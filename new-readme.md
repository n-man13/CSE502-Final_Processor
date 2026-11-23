# RV64IM Single-Issue Processor

This project implements a conservative single-issue, in-order RV64IM
processor. It has one architectural instruction stream and does not implement
superscalar dispatch or retirement.

## Pipeline structure

The processor uses explicit pipeline records:

1. IF/ID holds a fetched instruction and its PC.
2. ID/EX holds decoded operands, the destination register, immediate data,
   and control fields.
3. EX/MEM holds an execute result or memory effective address and control
   fields.
4. MEM/WB holds the value or memory result that may be committed.

Stages advance in program order. A branch or jump redirect invalidates younger
decode state and restarts instruction fetch at the redirect PC.

## Frontend

The frontend fetches 64-byte instruction lines through the 16 KiB instruction
L1 cache. The cache request and response interface is stalled until the line
is available. The processor accepts one instruction from the fetch buffer per
cycle.

## Decode and execute

The decoder translates RV32 instruction words into codewords. The ALU supports
the RV64I integer operations and RV64M multiply, divide, and remainder
operations used by the project.

Loads and stores use the 64 KiB write-back data L1 cache. Load values are
sign-extended or zero-extended according to the instruction size. Stores are
generated through the data-cache write interface and remain ordered through
memory writeback.

## Control hazards

Branches and jumps are resolved in execute. Taken redirects flush younger
pipeline state. Forwarding supplies EX/MEM and MEM/WB results to dependent
instructions. A load-use dependency stalls decode until the load is available.

## Memory and AXI

The cache wrappers share a small AXI arbiter:

- Instruction and data reads use eight-beat WRAP bursts.
- Data-cache writebacks use eight-beat INCR bursts.
- The arbiter gives no read/write response before all required beats complete.
- System snoops invalidate matching cache lines.

## Commit and system calls

Register writes occur only from valid MEM/WB entries. The architectural
register file never receives speculative writeback. Stores call
`do_pending_write` when accepted and `do_finish_write` after memory completion.
Committed ECALL instructions call `do_ecall` with register arguments and write
the returned value to register x10 where applicable.

## Verification

Build and test with the professor environment:

```bash
make
make run PROG="/opt/shared/cse502/tests/wp1/prog1"
cd mktest && make perf
make run PROG="mktest/test_perf"
```
