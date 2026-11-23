#!/usr/bin/env python3
"""Analyze prog1 trace.vcd for pipeline / memory behavior."""
from __future__ import annotations

import re
from collections import Counter, defaultdict

PATH = "trace.vcd"
WANT = {
    "clk",
    "reset",
    "pc",
    "fetch_pc",
    "fetch_instr",
    "fetch_valid",
    "redirect",
    "pipeline_stall",
    "load_use_stall",
    "i_pending",
    "d_pending",
    "zero_instr_count",
    "pipeline_all_zero",
    "m_axi_arvalid",
    "m_axi_araddr",
    "m_axi_arburst",
    "m_axi_arlen",
    "m_axi_rvalid",
    "m_axi_rlast",
    "m_axi_rready",
    "m_axi_awvalid",
    "m_axi_awaddr",
    "m_axi_awburst",
    "m_axi_awlen",
    "m_axi_wvalid",
    "m_axi_wlast",
}


def parse_int(val: str) -> int | None:
    if val in ("x", "X", "z", "Z") or any(c in "xXzZ" for c in val):
        return None
    return int(val, 2) if len(val) > 1 or val in "01" else int(val, 2)


def main() -> None:
    code_to_name: dict[str, str] = {}
    name_to_code: dict[str, str] = {}
    widths: dict[str, int] = {}
    values: dict[str, str] = {}

    end_t = 0
    timescale = "?"
    posedge_times: list[int] = []
    samples: list[dict] = []  # one per clk posedge after reset deassert

    reset_seen_low = False
    prev_clk = "0"
    t = 0

    # event timelines
    fetch_events: list[tuple[int, int, int]] = []  # t, pc, instr
    ar_events: list[tuple[int, int, int, int]] = []  # t, addr, burst, len
    aw_events: list[tuple[int, int]] = []
    redirect_times: list[int] = []
    stall_cycles = 0
    load_use_cycles = 0
    i_pending_cycles = 0
    d_pending_cycles = 0
    zero_fetch_cycles = 0
    valid_fetch_cycles = 0
    instr_hist: Counter[int] = Counter()
    pc_hist: Counter[int] = Counter()
    codeword_hint: Counter[str] = Counter()

    with open(PATH, "r", errors="replace") as f:
        for line in f:
            line = line.strip()
            if not line:
                continue
            if line.startswith("$timescale"):
                # may be "$timescale 1ps $end" on one line
                m = re.search(r"\$timescale\s+(\S+)", line)
                if m:
                    timescale = m.group(1)
                continue
            if line.startswith("$var"):
                parts = line.split()
                # $var wire <width> <code> <name> ...
                width = int(parts[2])
                code = parts[3]
                name = parts[4]
                # strip bus index
                name = re.sub(r"\[.*", "", name)
                if name in WANT or name.startswith(("if_id", "id_ex", "ex_mem", "mem_wb")):
                    # only exact WANT for values tracking to keep it light
                    if name in WANT:
                        code_to_name[code] = name
                        name_to_code[name] = code
                        widths[name] = width
                        values[name] = "x" * width if width > 1 else "x"
                continue
            if line.startswith("$enddefinitions"):
                print("Tracked signals:", sorted(name_to_code))
                continue
            if line.startswith("#"):
                t = int(line[1:])
                end_t = t
                continue

            # value change
            name = None
            val = None
            if line[0] in "01xXzZ" and len(line) >= 2 and not line.startswith("b"):
                val = line[0]
                code = line[1:]
                name = code_to_name.get(code)
            elif line.startswith("b") or line.startswith("B"):
                # b<data> <code>
                parts = line.split()
                if len(parts) >= 2:
                    val = parts[0][1:]
                    code = parts[1]
                    name = code_to_name.get(code)
            if name is None:
                continue

            old = values.get(name)
            values[name] = val

            # detect clk posedge
            if name == "clk" and old == "0" and val == "1":
                posedge_times.append(t)
                rst = values.get("reset", "1")
                if rst == "0":
                    reset_seen_low = True
                if not reset_seen_low or rst != "0":
                    continue

                def g(n: str) -> int | None:
                    return parse_int(values.get(n, "x"))

                pc = g("pc")
                fpc = g("fetch_pc")
                finstr = g("fetch_instr")
                fvalid = g("fetch_valid")
                redir = g("redirect")
                pstall = g("pipeline_stall")
                lustall = g("load_use_stall")
                ip = g("i_pending")
                dp = g("d_pending")
                zc = g("zero_instr_count")
                arvalid = g("m_axi_arvalid")
                araddr = g("m_axi_araddr")
                arburst = g("m_axi_arburst")
                arlen = g("m_axi_arlen")
                awvalid = g("m_axi_awvalid")
                awaddr = g("m_axi_awaddr")

                if pstall == 1:
                    stall_cycles += 1
                if lustall == 1:
                    load_use_cycles += 1
                if ip == 1:
                    i_pending_cycles += 1
                if dp == 1:
                    d_pending_cycles += 1
                if redir == 1:
                    redirect_times.append(t)

                if fvalid == 1 and finstr is not None:
                    valid_fetch_cycles += 1
                    instr_hist[finstr] += 1
                    if fpc is not None:
                        pc_hist[fpc] += 1
                    if finstr == 0:
                        zero_fetch_cycles += 1
                    fetch_events.append((t, fpc or -1, finstr))
                    # rough opcode classify
                    opc = finstr & 0x7F
                    if finstr == 0:
                        codeword_hint["ZERO/NOP"] += 1
                    elif opc == 0x13:
                        codeword_hint["OP-IMM"] += 1
                    elif opc == 0x33:
                        codeword_hint["OP"] += 1
                    elif opc == 0x03:
                        codeword_hint["LOAD"] += 1
                    elif opc == 0x23:
                        codeword_hint["STORE"] += 1
                    elif opc == 0x63:
                        codeword_hint["BRANCH"] += 1
                    elif opc == 0x6F:
                        codeword_hint["JAL"] += 1
                    elif opc == 0x67:
                        codeword_hint["JALR"] += 1
                    elif opc == 0x37:
                        codeword_hint["LUI"] += 1
                    elif opc == 0x17:
                        codeword_hint["AUIPC"] += 1
                    elif opc == 0x73:
                        codeword_hint["SYSTEM"] += 1
                    elif opc == 0x1B:
                        codeword_hint["OP-IMM-32"] += 1
                    elif opc == 0x3B:
                        codeword_hint["OP-32"] += 1
                    else:
                        codeword_hint[f"OTHER(opc={opc:#x})"] += 1

                if arvalid == 1 and araddr is not None:
                    # record only when arvalid rises or periodically; use change detect via list uniqueness by time
                    if not ar_events or ar_events[-1][0] != t:
                        ar_events.append((t, araddr, arburst or -1, arlen or -1))
                if awvalid == 1 and awaddr is not None:
                    if not aw_events or aw_events[-1][0] != t:
                        aw_events.append((t, awaddr))

                # keep sparse sample log: first 40 post-reset cycles + every 500th
                cyc = len(posedge_times)
                if cyc <= 40 or cyc % 500 == 0:
                    samples.append(
                        {
                            "t": t,
                            "pc": pc,
                            "fetch_pc": fpc,
                            "fetch_instr": finstr,
                            "fetch_valid": fvalid,
                            "redirect": redir,
                            "stall": pstall,
                            "i_pending": ip,
                            "arvalid": arvalid,
                            "araddr": araddr,
                            "zero_cnt": zc,
                        }
                    )

    cycles = len(posedge_times)
    active = stall_cycles  # placeholder
    print("\n=== TRACE SUMMARY (prog1) ===")
    print(f"timescale: {timescale}")
    print(f"end_time: {end_t} ({end_t/1e6:.3f} us if ps)")
    print(f"clock_posedges: {cycles}")
    if cycles >= 2:
        dt = posedge_times[1] - posedge_times[0]
        print(f"clock_period: {dt} {timescale} ({1e12/dt if timescale=='1ps' else 'n/a'} Hz nominal)")
    print(f"post-reset valid fetches: {valid_fetch_cycles}")
    print(f"zero instruction fetches: {zero_fetch_cycles}")
    print(f"pipeline_stall cycles: {stall_cycles}")
    print(f"load_use_stall cycles: {load_use_cycles}")
    print(f"i_pending cycles: {i_pending_cycles}")
    print(f"d_pending cycles: {d_pending_cycles}")
    print(f"redirect events: {len(redirect_times)}")
    print(f"AXI AR handshakes sampled: {len(ar_events)}")
    print(f"AXI AW handshakes sampled: {len(aw_events)}")

    print("\n--- Opcode mix (fetched, valid) ---")
    for k, v in codeword_hint.most_common():
        print(f"  {k}: {v}")

    print("\n--- Top fetch PCs ---")
    for pc, v in pc_hist.most_common(15):
        print(f"  pc={pc:#x}: {v}")

    print("\n--- First 25 valid fetches ---")
    for i, (tt, pc, instr) in enumerate(fetch_events[:25]):
        print(f"  [{i:02d}] t={tt} pc={pc:#x} instr={instr:08x}")

    print("\n--- Last 15 valid fetches ---")
    for i, (tt, pc, instr) in enumerate(fetch_events[-15:]):
        print(f"  [{len(fetch_events)-15+i:02d}] t={tt} pc={pc:#x} instr={instr:08x}")

    print("\n--- AXI read requests (first 20) ---")
    for tt, addr, burst, alen in ar_events[:20]:
        bname = {1: "INCR", 2: "WRAP"}.get(burst, str(burst))
        print(f"  t={tt} araddr={addr:#x} burst={bname} len={alen} (beats={alen+1 if alen>=0 else '?'})")

    print("\n--- AXI write requests (first 10) ---")
    for tt, addr in aw_events[:10]:
        print(f"  t={tt} awaddr={addr:#x}")

    # detect if PC stuck
    if fetch_events:
        last_pcs = [pc for _, pc, _ in fetch_events[-50:]]
        unique_last = len(set(last_pcs))
        print(f"\nUnique PCs in last 50 fetches: {unique_last}")
        # long runs of same PC
        max_run = 1
        run = 1
        for a, b in zip(last_pcs, last_pcs[1:]):
            if a == b:
                run += 1
                max_run = max(max_run, run)
            else:
                run = 1
        print(f"Max consecutive same-PC streak in last 50: {max_run}")

    # early timeline samples
    print("\n--- Early/sparse cycle samples ---")
    for s in samples[:30]:
        fi = s["fetch_instr"]
        fi_s = f"{fi:08x}" if isinstance(fi, int) else str(fi)
        pc_s = f"{s['pc']:#x}" if isinstance(s["pc"], int) else str(s["pc"])
        fpc_s = f"{s['fetch_pc']:#x}" if isinstance(s["fetch_pc"], int) else str(s["fetch_pc"])
        ara = f"{s['araddr']:#x}" if isinstance(s["araddr"], int) else str(s["araddr"])
        print(
            f"  t={s['t']:>10} pc={pc_s:>18} fpc={fpc_s:>18} finstr={fi_s} "
            f"fv={s['fetch_valid']} st={s['stall']} ip={s['i_pending']} "
            f"ar={s['arvalid']} ara={ara} zc={s['zero_cnt']}"
        )


if __name__ == "__main__":
    main()
