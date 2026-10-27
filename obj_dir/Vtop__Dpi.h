// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Prototypes for DPI import and export functions.
//
// Verilator includes this file in all generated .cpp files that use DPI functions.
// Manually include this file where DPI .c import functions are declared to ensure
// the C functions match the expectations of the DPI imports.

#ifndef VERILATED_VTOP__DPI_H_
#define VERILATED_VTOP__DPI_H_  // guard

#include "svdpi.h"

#ifdef __cplusplus
extern "C" {
#endif


    // DPI IMPORTS
    // DPI import at Sysbus.defs:11:1
    extern void do_ecall(long long a7, long long a0, long long a1, long long a2, long long a3, long long a4, long long a5, long long a6, long long* a0ret);
    // DPI import at Sysbus.defs:7:1
    extern void do_finish_write(long long addr, int size);
    // DPI import at Sysbus.defs:3:1
    extern void do_pending_write(long long addr, long long val, int size);

#ifdef __cplusplus
}
#endif

#endif  // guard
