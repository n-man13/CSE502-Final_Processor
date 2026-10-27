// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop__pch.h"
#include "Vtop__Syms.h"
#include "Vtop___024unit.h"

extern "C" void do_pending_write(long long addr, long long val, int size);

VL_INLINE_OPT void Vtop___024unit____Vdpiimwrap_do_pending_write_TOP____024unit(QData/*63:0*/ addr, QData/*63:0*/ val, IData/*31:0*/ size) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vtop___024unit____Vdpiimwrap_do_pending_write_TOP____024unit\n"); );
    // Body
    long long addr__Vcvt;
    for (size_t addr__Vidx = 0; addr__Vidx < 1; ++addr__Vidx) addr__Vcvt = addr;
    long long val__Vcvt;
    for (size_t val__Vidx = 0; val__Vidx < 1; ++val__Vidx) val__Vcvt = val;
    int size__Vcvt;
    for (size_t size__Vidx = 0; size__Vidx < 1; ++size__Vidx) size__Vcvt = size;
    do_pending_write(addr__Vcvt, val__Vcvt, size__Vcvt);
}

extern "C" void do_finish_write(long long addr, int size);

VL_INLINE_OPT void Vtop___024unit____Vdpiimwrap_do_finish_write_TOP____024unit(QData/*63:0*/ addr, IData/*31:0*/ size) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vtop___024unit____Vdpiimwrap_do_finish_write_TOP____024unit\n"); );
    // Body
    long long addr__Vcvt;
    for (size_t addr__Vidx = 0; addr__Vidx < 1; ++addr__Vidx) addr__Vcvt = addr;
    int size__Vcvt;
    for (size_t size__Vidx = 0; size__Vidx < 1; ++size__Vidx) size__Vcvt = size;
    do_finish_write(addr__Vcvt, size__Vcvt);
}

extern "C" void do_ecall(long long a7, long long a0, long long a1, long long a2, long long a3, long long a4, long long a5, long long a6, long long* a0ret);

VL_INLINE_OPT void Vtop___024unit____Vdpiimwrap_do_ecall_TOP____024unit(QData/*63:0*/ a7, QData/*63:0*/ a0, QData/*63:0*/ a1, QData/*63:0*/ a2, QData/*63:0*/ a3, QData/*63:0*/ a4, QData/*63:0*/ a5, QData/*63:0*/ a6, QData/*63:0*/ &a0ret) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vtop___024unit____Vdpiimwrap_do_ecall_TOP____024unit\n"); );
    // Body
    long long a7__Vcvt;
    for (size_t a7__Vidx = 0; a7__Vidx < 1; ++a7__Vidx) a7__Vcvt = a7;
    long long a0__Vcvt;
    for (size_t a0__Vidx = 0; a0__Vidx < 1; ++a0__Vidx) a0__Vcvt = a0;
    long long a1__Vcvt;
    for (size_t a1__Vidx = 0; a1__Vidx < 1; ++a1__Vidx) a1__Vcvt = a1;
    long long a2__Vcvt;
    for (size_t a2__Vidx = 0; a2__Vidx < 1; ++a2__Vidx) a2__Vcvt = a2;
    long long a3__Vcvt;
    for (size_t a3__Vidx = 0; a3__Vidx < 1; ++a3__Vidx) a3__Vcvt = a3;
    long long a4__Vcvt;
    for (size_t a4__Vidx = 0; a4__Vidx < 1; ++a4__Vidx) a4__Vcvt = a4;
    long long a5__Vcvt;
    for (size_t a5__Vidx = 0; a5__Vidx < 1; ++a5__Vidx) a5__Vcvt = a5;
    long long a6__Vcvt;
    for (size_t a6__Vidx = 0; a6__Vidx < 1; ++a6__Vidx) a6__Vcvt = a6;
    long long a0ret__Vcvt;
    do_ecall(a7__Vcvt, a0__Vcvt, a1__Vcvt, a2__Vcvt, a3__Vcvt, a4__Vcvt, a5__Vcvt, a6__Vcvt, &a0ret__Vcvt);
    a0ret = a0ret__Vcvt;
}
