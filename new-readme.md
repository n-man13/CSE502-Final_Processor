# RV64IM In-Order Superscalar Processor Plan

This document describes the methodology for evolving this project into an
RV64IM superscalar, in-order processor. The recommended starting point is a
two-wide machine: it can accept up to two instructions per cycle, but it
executes and commits them in program order. A wider implementation is
possible, but two-wide exposes the important superscalar mechanisms without
making verification unnecessarily difficult.

The existing SystemVerilog file already contains useful building blocks:

- `decoder` translates a 32-bit instruction into a `codeword_t`.
- `regfile` provides 32 64-bit integer registers and initializes `x2` (`sp`).
- `alu` implements most RV64I and RV64M integer operations.
- `l1_i_cache` and `l1_d_cache` provide separate instruction and data-cache
  interfaces. Their default capacities are 16 KiB and 64 KiB respectively;
  both retain 32-byte lines and two ways.
- `top` currently fetches one 64-byte line directly through AXI, decodes one
  instruction, and advances the PC.

The current `top` is therefore a useful prototype, not yet a complete
processor pipeline. In particular, its write-enable and PC logic are not a
complete execute, memory, or commit implementation, and its AXI write channel
is tied off. The work below should be treated as an integration plan rather
than an assumption that all of the final behavior already exists.

## 1. Architectural target

The target machine should implement:

- RV64I integer instructions required by the project.
- RV64M multiply, divide, and remainder instructions.
- 64-bit registers and addresses.
- Two instructions dispatched per cycle when they are independent and both
  pipeline slots are available.
- In-order execution and in-order retirement.
- Separate instruction and data L1 caches.
- A single, precise architectural state: PC, registers, memory, and any
  supported CSRs.
- Correct behavior for branches, jumps, loads, stores, `ECALL`, and traps or
  unsupported instructions according to the project specification.

“Superscalar” does not mean that every pair must execute in parallel. The
front end may provide two instructions, while the issue logic may safely
accept only one when there is a dependency, a branch, a cache miss, a
multi-cycle operation, or an ordering constraint.

## 2. Recommended pipeline organization

Use explicit valid bits and pipeline registers between these stages:

1. **Fetch (IF)** — obtain an instruction line and select up to two
   instructions.
2. **Decode and rename/read (ID)** — decode both instructions and read their
   source operands.
3. **Issue/execute (EX)** — check dependencies, select functional units, and
   calculate ALU results, branch targets, and effective addresses.
4. **Memory (MEM)** — access the data cache for loads and stores.
5. **Writeback/commit (WB)** — write registers and retire side effects in
   program order.

The names may be combined in RTL, but the interfaces and control responsibilities
should remain explicit. Every stage must support `valid`, `ready` or stall
behavior, and a flush input for redirects. A pipeline register must not be
updated with an invalid entry, and it must be held while the downstream stage
is stalled.

## 3. Stage-by-stage inputs and outputs

### 3.1 Fetch (IF)

**Inputs**

- `clk`, `reset`, and flush/redirect control.
- The current fetch PC.
- Instruction-cache request `ready`.
- Instruction-cache response valid and 64-bit data beats.
- Redirect PC from branch/jump resolution.

**Outputs**

- Instruction-cache request valid and aligned line address.
- Fetch PC for the line and the byte offset of the first instruction.
- An IF/ID entry containing up to two 32-bit instructions, their PCs, and
  valid bits.
- The next sequential PC (`pc + 4` per instruction).

The `instruction_fetch` module in `top.sv` owns the fetch PC, 64-byte line
buffer, AXI read state machine, and `fetch_valid`/`fetch_instr` interface.
The top-level execution path consumes a valid instruction through that
interface instead of owning the fetch state machine.

The AXI contract in [README.md](C:/Users/nikis/architecture/CSE502-Final_Processor/README.md)
requires 64-byte reads as eight 64-bit beats, with `arlen = 7`, `arsize = 3`,
and a WRAP burst. The fetch unit should request a line aligned to 64 bytes,
retain the returned line, and select instructions using the PC offset. It
must handle a line boundary: the second slot is invalid if its instruction is
not in the current line, and the next fetch supplies it later.

Do not increment the architectural PC merely because a request was issued.
Advance the fetch PC when an instruction pair is accepted into the next
pipeline stage. On a taken branch or jump, invalidate younger fetched
instructions and restart at the target.

### 3.2 Decode and register read (ID)

**Inputs**

- Up to two valid instructions and their PCs from IF.
- Register-file read values for `rs1` and `rs2`.
- Older in-flight destination metadata for forwarding or hazard detection.
- Flush and stall signals.

**Outputs**

- An ID/EX entry per slot containing:
  - valid bit and PC;
  - `codeword`, `rd`, `rs1`, `rs2`;
  - sign- or zero-extended immediate;
  - source operand values or source register identifiers;
  - operand-select controls;
  - register-write, memory-read, memory-write, branch, jump, and system-op
    controls;
  - load/store width and byte-enable information.

The existing [top.sv](C:/Users/nikis/architecture/CSE502-Final_Processor/top.sv)
`decoder` should be reused and extended only where required. Immediate
generation must be instruction-specific: I, S, B, U, and J formats have
different bit layouts. Shift-immediate instructions must validate their
upper bits, and RV64 word operations must produce sign-extended 64-bit
results.

The register file has two architectural read ports and one write port. A
two-wide front end needs four source operands in the general case. Either
add read ports, or read the register file once per slot and add explicit
operand forwarding. Always force `x0` to zero and never create a dependency
on a write to `rd = 0`.

### 3.3 Issue and execute (EX)

**Inputs**

- Up to two decoded entries.
- Forwarded values from later stages.
- Functional-unit availability.
- Data-cache request readiness.

**Outputs**

- ALU result for arithmetic, logical, shift, and compare operations.
- Branch condition and redirect target.
- Jump link value (`PC + 4`) and target.
- Effective address and store data for memory operations.
- EX/MEM entries containing destination and side-effect controls.
- Stall, replay, or flush requests.

The issue logic is the defining superscalar component. It must enforce
in-order issue when a pair is unsafe:

- Slot 1 writes a register read by slot 2.
- Slot 1 is a load and slot 2 consumes the loaded value.
- Either instruction is a branch, jump, `ECALL`, `EBREAK`, or fence.
- A required functional unit is busy.
- A store must remain ordered with an older load/store according to the
  chosen memory model.

Begin with conservative rules: issue slot 2 only when all of its operands
are available and no older instruction can change the control-flow or memory
ordering. Correctness is more important than filling both slots.

Branches and jumps should resolve as early as practical, preferably in EX.
When a redirect is taken, assert a pipeline flush for all younger entries,
discard their register and memory controls, and set the fetch PC to the
target. The link register for `JAL`/`JALR` is committed like any other
register result.

RV64M operations need special care. Multiplication can be a combinational
unit initially, but division and remainder should be modeled as a
multi-cycle unit with `busy` and `done` signals, or the whole pipeline will
appear to execute out of order when a divide takes multiple cycles.

### 3.4 Memory (MEM)

**Inputs**

- EX/MEM entries with effective addresses.
- Store data and byte enables.
- Data-cache request readiness and response data.
- Flush and exception controls.

**Outputs**

- Data-cache request valid, read/write bit, address, data, and strobes.
- Load response and correctly extended load value.
- MEM/WB entries for completed instructions.
- A stall while a cache miss or load response is outstanding.

The data cache interface in [top.sv](C:/Users/nikis/architecture/CSE502-Final_Processor/top.sv)
uses a 64-bit CPU-side transfer and an 8-bit write strobe. Generate strobes
from the effective-address low bits and access size:

- `LB`/`LBU`: one byte;
- `LH`/`LHU`: two bytes;
- `LW`/`LWU`: four bytes;
- `LD`: eight bytes.

Load data must be shifted to the addressed byte and then sign- or
zero-extended. Store data must be shifted to the addressed byte lane before
being sent to the cache. Misaligned accesses should either be rejected or
implemented consistently with the project specification; do not silently
perform an incorrect aligned access.

Stores must not update architectural memory until they are safe to commit.
The testbench exposes `do_pending_write` when a store commits and
`do_finish_write` when the write reaches memory. Keep this distinction in
the design. A cache writeback is not the same event as an architectural store
retirement.

### 3.5 Writeback and commit (WB)

**Inputs**

- Completed MEM/WB entries.
- ALU, multiply/divide, load, branch, and system-call results.
- Register-file write availability.
- Exception or flush status.

**Outputs**

- At most two in-order register-file writes.
- Committed store and `do_pending_write` notification.
- Updated PC/CSR state for system operations.
- Retirement count and optional trace/debug information.

Commit is the architectural correctness boundary. Retire slot 1 before slot
2, and retire slot 2 only if slot 1 is valid and does not redirect or trap.
An instruction that is flushed must not write a register, perform a store, or
invoke `ECALL`. Register writes must be suppressed for `UNKNOWN`, fences that
have no modeled destination, and `rd = 0`.

For `ECALL`, collect `a0` through `a7` from the committed register state,
invoke the DPI function described in
[Sysbus.defs](C:/Users/nikis/architecture/CSE502-Final_Processor/Sysbus.defs),
and write the returned `a0` value only when the call completes according to
the project convention. Keep this side effect ordered and non-speculative.

## 4. Pipeline control and hazards

### Data hazards

Implement the following in order:

1. **Same-cycle write/read bypass** from WB to decode.
2. **EX/MEM forwarding** for ALU and branch operands.
3. **MEM/WB forwarding** for ALU results and completed loads.
4. **Load-use interlock**: stall the consumer until load data is available.
5. **Two-wide intra-pair dependency checks**.

Each pipeline entry should carry `rd`, `reg_write`, and `valid`, so hazard
logic does not need to decode the instruction again.

### Structural hazards

Track availability for the ALU, multiplier/divider, instruction cache, data
cache, and register-file write ports. If two instructions need a resource
that cannot accept both, hold the second instruction and preserve ordering.

### Control hazards

Predict not-taken initially. Fetch may proceed speculatively, but a taken
branch or jump must flush all younger instructions. Add a branch predictor
only after the unpredicted design passes the functional tests; prediction
must never change architectural results.

### Backpressure and flush priority

Use a consistent priority:

1. reset;
2. exception or committed system operation;
3. taken redirect;
4. downstream stall/hold;
5. normal pipeline advance.

This avoids accepting a new instruction into a stage that is being flushed.

## 5. Memory system and AXI integration

Connect the instruction and data caches instead of maintaining separate,
ad-hoc AXI logic in `top`. A small arbiter or shared memory request unit must
translate cache line requests to the AXI signals already consumed by
`system.cpp`:

- reads: eight-beat, 64-byte WRAP bursts;
- writes: eight-beat INCR bursts;
- `rready` only when the receiving cache can accept the beat;
- stable address/control signals while `valid` is asserted without `ready`;
- one response per outstanding transaction, matched by ID if concurrency is
  added.

Handle `m_axi_acvalid` snoops by invalidating matching cache lines. This is
required after a system call modifies memory. A cache that ignores snoops can
return stale instructions or data.

If virtual memory is enabled with `HAVETLB=y`, translation must occur before
cache lookup or in a clearly defined VIPT/PIPT design. The simplest
methodology is to implement bare physical addressing first, then add an Sv48
TLB and page-walk state machine. Do not mix partial translation into the
pipeline until the non-TLB core is stable.

## 6. Implementation methodology

Work in milestones, keeping the design runnable after each milestone:

1. **Define pipeline records and timing.** Create typed IF/ID, ID/EX, EX/MEM,
   and MEM/WB structures with valid, stall, flush, and control fields.
2. **Separate fetch from execution.** Replace the current `top` state machine
   with an instruction-cache request/response path and a fetch buffer.
3. **Make one instruction fully functional.** Implement immediate generation,
   ALU execution, register writeback, and sequential PC updates.
4. **Add loads and stores.** Integrate `l1_d_cache`, byte enables, extension,
   writeback, and store commit notifications.
5. **Add control flow.** Implement B-type and J-type immediates, target
   calculation, redirect, and flushing.
6. **Add hazards and forwarding.** First make a single-issue pipeline correct,
   then add conservative two-wide checks.
7. **Add RV64M multi-cycle behavior.** Verify divide-by-zero and signed
   overflow behavior against the ISA.
8. **Enable two-wide dispatch.** Allow slot 2 only when hazard, resource,
   control, and memory-order checks pass.
9. **Add fences, CSR/system instructions, and `ECALL`** required by the
   supplied programs.
10. **Add optional TLB and branch prediction** only after baseline tests pass.

Keep the architectural state separate from pipeline state. A flush clears
pipeline valid bits; it must not clear the register file or cache contents.
Prefer explicit state machines for cache misses, division, and page walks over
implicit timing assumptions.

## 7. Verification strategy

Run the smallest test after each change, then expand coverage:

- Hand-written `mktest` programs for each instruction format.
- Register dependency tests, including two instructions in one cycle.
- Load-use, store-after-load, and store ordering tests.
- Taken and not-taken branches, backward loops, `JAL`, and `JALR`.
- RV64 sign extension and RV64W upper-32-bit behavior.
- RV64M divide-by-zero, remainder, and `INT64_MIN / -1`.
- Cache misses, dirty evictions, line boundaries, and snoop invalidation.
- `ECALL` and programs that terminate on an all-zero instruction.
- The supplied `wp1`, `wp2`, and project binaries through `make run`.

Use Verilator warnings, assertions, and waveforms to inspect valid bits,
PCs, instruction IDs, destination registers, cache handshakes, and commit
events. A useful trace includes one monotonically increasing instruction
sequence number per fetched instruction. Compare committed register and
memory state against a reference model, not merely against intermediate
pipeline signals.

## 8. Most important changes

The following changes have the highest impact on completing the processor:

1. **Replace the current top-level fetch/decode loop with real pipeline
   registers and valid/ready control.** Without this, there is no reliable
   stall, flush, or superscalar behavior.
2. **Integrate the existing instruction and data caches with AXI.** The
   current top-level write channel is tied off, so stores cannot work.
3. **Implement complete instruction semantics and immediate generation.**
   The decoder and ALU are helpful, but memory, branches, jumps, system
   operations, and several control paths still need integration.
4. **Implement forwarding, load-use stalls, and two-wide dependency checks.**
   These are necessary to prevent incorrect register values.
5. **Make commit precise and in order.** This protects architectural state
   from speculative instructions and makes branches, stores, and `ECALL`
   behavior deterministic.
6. **Model multi-cycle division and cache misses explicitly.** Treating them
   as single-cycle operations creates hidden ordering bugs.
7. **Verify against the project’s exact bus and DPI contracts.** Correct
   instruction results are insufficient if burst lengths, strobes, snoops, or
   commit callbacks are wrong.

The safest performance strategy is to begin conservatively: single-issue
execution with complete correctness, then enable two-wide issue only for
independent ALU instructions. Once that path is verified, widen memory and
multi-cycle-unit scheduling incrementally. This produces a measurable
superscalar processor without making every pipeline feature speculative at
the same time.
