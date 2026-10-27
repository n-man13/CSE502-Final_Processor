// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop__pch.h"
#include "Vtop__Syms.h"
#include "Vtop___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(Vtop___024root* vlSelf);
#endif  // VL_DEBUG

void Vtop___024root___eval_triggers__act(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_triggers__act\n"); );
    // Body
    vlSelf->__VactTriggered.set(0U, ((IData)(vlSelf->clk) 
                                     & (~ (IData)(vlSelf->__Vtrigprevexpr___TOP__clk__0))));
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = vlSelf->clk;
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vtop___024root___dump_triggers__act(vlSelf);
    }
#endif
}

VL_INLINE_OPT void Vtop___024root___nba_sequent__TOP__0(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__0\n"); );
    // Init
    QData/*63:0*/ top__DOT__immediate;
    top__DOT__immediate = 0;
    QData/*63:0*/ top__DOT__alu_a;
    top__DOT__alu_a = 0;
    QData/*63:0*/ top__DOT__alu_b;
    top__DOT__alu_b = 0;
    QData/*63:0*/ top__DOT____VdfgExtracted_h6b31312d__0;
    top__DOT____VdfgExtracted_h6b31312d__0 = 0;
    CData/*6:0*/ top__DOT__decode__DOT__opcode;
    top__DOT__decode__DOT__opcode = 0;
    CData/*2:0*/ top__DOT__decode__DOT__funct3;
    top__DOT__decode__DOT__funct3 = 0;
    CData/*6:0*/ top__DOT__decode__DOT__funct7;
    top__DOT__decode__DOT__funct7 = 0;
    VlWide<4>/*127:0*/ top__DOT__execute_alu__DOT__signed_product;
    VL_ZERO_W(128, top__DOT__execute_alu__DOT__signed_product);
    VlWide<4>/*127:0*/ top__DOT__execute_alu__DOT__signed_unsigned_product;
    VL_ZERO_W(128, top__DOT__execute_alu__DOT__signed_unsigned_product);
    VlWide<4>/*127:0*/ top__DOT__execute_alu__DOT__unsigned_product;
    VL_ZERO_W(128, top__DOT__execute_alu__DOT__unsigned_product);
    IData/*31:0*/ top__DOT__execute_alu__DOT__word_result;
    top__DOT__execute_alu__DOT__word_result = 0;
    QData/*63:0*/ __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout;
    __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout = 0;
    std::string __Vfunc_top__DOT__codeword_text__1__Vfuncout;
    CData/*6:0*/ __Vfunc_top__DOT__codeword_text__1__value;
    __Vfunc_top__DOT__codeword_text__1__value = 0;
    std::string __Vfunc_top__DOT__codeword_text__2__Vfuncout;
    CData/*6:0*/ __Vfunc_top__DOT__codeword_text__2__value;
    __Vfunc_top__DOT__codeword_text__2__value = 0;
    QData/*63:0*/ __Vdly__top__DOT__pc;
    __Vdly__top__DOT__pc = 0;
    CData/*2:0*/ __Vdly__top__DOT__beat_count;
    __Vdly__top__DOT__beat_count = 0;
    CData/*1:0*/ __Vdly__top__DOT__state;
    __Vdly__top__DOT__state = 0;
    CData/*0:0*/ __Vdlyvset__top__DOT__registers__DOT__regs__v0;
    __Vdlyvset__top__DOT__registers__DOT__regs__v0 = 0;
    QData/*63:0*/ __Vdlyvval__top__DOT__registers__DOT__regs__v32;
    __Vdlyvval__top__DOT__registers__DOT__regs__v32 = 0;
    CData/*4:0*/ __Vdlyvdim0__top__DOT__registers__DOT__regs__v33;
    __Vdlyvdim0__top__DOT__registers__DOT__regs__v33 = 0;
    QData/*63:0*/ __Vdlyvval__top__DOT__registers__DOT__regs__v33;
    __Vdlyvval__top__DOT__registers__DOT__regs__v33 = 0;
    CData/*0:0*/ __Vdlyvset__top__DOT__registers__DOT__regs__v33;
    __Vdlyvset__top__DOT__registers__DOT__regs__v33 = 0;
    std::string __Vtemp_1;
    std::string __Vtemp_2;
    VlWide<4>/*127:0*/ __Vtemp_3;
    VlWide<4>/*127:0*/ __Vtemp_4;
    VlWide<4>/*127:0*/ __Vtemp_5;
    VlWide<4>/*127:0*/ __Vtemp_6;
    VlWide<4>/*127:0*/ __Vtemp_7;
    VlWide<4>/*127:0*/ __Vtemp_8;
    // Body
    __Vdlyvset__top__DOT__registers__DOT__regs__v0 = 0U;
    __Vdlyvset__top__DOT__registers__DOT__regs__v33 = 0U;
    __Vdly__top__DOT__beat_count = vlSelf->top__DOT__beat_count;
    __Vdly__top__DOT__state = vlSelf->top__DOT__state;
    __Vdly__top__DOT__pc = vlSelf->top__DOT__pc;
    if (vlSelf->reset) {
        __Vdlyvset__top__DOT__registers__DOT__regs__v0 = 1U;
        __Vdlyvval__top__DOT__registers__DOT__regs__v32 
            = vlSelf->stackptr;
    } else if (((((3U == (IData)(vlSelf->top__DOT__state)) 
                  & (IData)(vlSelf->top__DOT__has_rd)) 
                 & (0U != (IData)(vlSelf->top__DOT__codeword))) 
                & (0U != (0x1fU & (vlSelf->top__DOT__instr 
                                   >> 7U))))) {
        __Vdlyvval__top__DOT__registers__DOT__regs__v33 
            = vlSelf->top__DOT__alu_result;
        __Vdlyvset__top__DOT__registers__DOT__regs__v33 = 1U;
        __Vdlyvdim0__top__DOT__registers__DOT__regs__v33 
            = (0x1fU & (vlSelf->top__DOT__instr >> 7U));
    }
    if (vlSelf->reset) {
        __Vdly__top__DOT__pc = vlSelf->entry;
        __Vdly__top__DOT__beat_count = 0U;
        __Vdly__top__DOT__state = 0U;
    } else if ((2U & (IData)(vlSelf->top__DOT__state))) {
        if ((1U & (IData)(vlSelf->top__DOT__state))) {
            if (VL_UNLIKELY((0U == vlSelf->top__DOT__instr))) {
                VL_WRITEF("Register 0: 0000000000000000\n");
                VL_WRITEF("Register 1: %016x\n",64,
                          ([&]() {
                                __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout 
                                    = vlSelf->top__DOT__registers__DOT__regs
                                    [1U];
                            }(), __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout));
                VL_WRITEF("Register 2: %016x\n",64,
                          ([&]() {
                                __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout 
                                    = vlSelf->top__DOT__registers__DOT__regs
                                    [2U];
                            }(), __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout));
                VL_WRITEF("Register 3: %016x\n",64,
                          ([&]() {
                                __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout 
                                    = vlSelf->top__DOT__registers__DOT__regs
                                    [3U];
                            }(), __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout));
                VL_WRITEF("Register 4: %016x\n",64,
                          ([&]() {
                                __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout 
                                    = vlSelf->top__DOT__registers__DOT__regs
                                    [4U];
                            }(), __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout));
                VL_WRITEF("Register 5: %016x\n",64,
                          ([&]() {
                                __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout 
                                    = vlSelf->top__DOT__registers__DOT__regs
                                    [5U];
                            }(), __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout));
                VL_WRITEF("Register 6: %016x\n",64,
                          ([&]() {
                                __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout 
                                    = vlSelf->top__DOT__registers__DOT__regs
                                    [6U];
                            }(), __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout));
                VL_WRITEF("Register 7: %016x\n",64,
                          ([&]() {
                                __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout 
                                    = vlSelf->top__DOT__registers__DOT__regs
                                    [7U];
                            }(), __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout));
                VL_WRITEF("Register 8: %016x\n",64,
                          ([&]() {
                                __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout 
                                    = vlSelf->top__DOT__registers__DOT__regs
                                    [8U];
                            }(), __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout));
                VL_WRITEF("Register 9: %016x\n",64,
                          ([&]() {
                                __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout 
                                    = vlSelf->top__DOT__registers__DOT__regs
                                    [9U];
                            }(), __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout));
                VL_WRITEF("Register 10: %016x\n",64,
                          ([&]() {
                                __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout 
                                    = vlSelf->top__DOT__registers__DOT__regs
                                    [0xaU];
                            }(), __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout));
                VL_WRITEF("Register 11: %016x\n",64,
                          ([&]() {
                                __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout 
                                    = vlSelf->top__DOT__registers__DOT__regs
                                    [0xbU];
                            }(), __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout));
                VL_WRITEF("Register 12: %016x\n",64,
                          ([&]() {
                                __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout 
                                    = vlSelf->top__DOT__registers__DOT__regs
                                    [0xcU];
                            }(), __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout));
                VL_WRITEF("Register 13: %016x\n",64,
                          ([&]() {
                                __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout 
                                    = vlSelf->top__DOT__registers__DOT__regs
                                    [0xdU];
                            }(), __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout));
                VL_WRITEF("Register 14: %016x\n",64,
                          ([&]() {
                                __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout 
                                    = vlSelf->top__DOT__registers__DOT__regs
                                    [0xeU];
                            }(), __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout));
                VL_WRITEF("Register 15: %016x\n",64,
                          ([&]() {
                                __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout 
                                    = vlSelf->top__DOT__registers__DOT__regs
                                    [0xfU];
                            }(), __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout));
                VL_WRITEF("Register 16: %016x\n",64,
                          ([&]() {
                                __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout 
                                    = vlSelf->top__DOT__registers__DOT__regs
                                    [0x10U];
                            }(), __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout));
                VL_WRITEF("Register 17: %016x\n",64,
                          ([&]() {
                                __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout 
                                    = vlSelf->top__DOT__registers__DOT__regs
                                    [0x11U];
                            }(), __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout));
                VL_WRITEF("Register 18: %016x\n",64,
                          ([&]() {
                                __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout 
                                    = vlSelf->top__DOT__registers__DOT__regs
                                    [0x12U];
                            }(), __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout));
                VL_WRITEF("Register 19: %016x\n",64,
                          ([&]() {
                                __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout 
                                    = vlSelf->top__DOT__registers__DOT__regs
                                    [0x13U];
                            }(), __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout));
                VL_WRITEF("Register 20: %016x\n",64,
                          ([&]() {
                                __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout 
                                    = vlSelf->top__DOT__registers__DOT__regs
                                    [0x14U];
                            }(), __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout));
                VL_WRITEF("Register 21: %016x\n",64,
                          ([&]() {
                                __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout 
                                    = vlSelf->top__DOT__registers__DOT__regs
                                    [0x15U];
                            }(), __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout));
                VL_WRITEF("Register 22: %016x\n",64,
                          ([&]() {
                                __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout 
                                    = vlSelf->top__DOT__registers__DOT__regs
                                    [0x16U];
                            }(), __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout));
                VL_WRITEF("Register 23: %016x\n",64,
                          ([&]() {
                                __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout 
                                    = vlSelf->top__DOT__registers__DOT__regs
                                    [0x17U];
                            }(), __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout));
                VL_WRITEF("Register 24: %016x\n",64,
                          ([&]() {
                                __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout 
                                    = vlSelf->top__DOT__registers__DOT__regs
                                    [0x18U];
                            }(), __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout));
                VL_WRITEF("Register 25: %016x\n",64,
                          ([&]() {
                                __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout 
                                    = vlSelf->top__DOT__registers__DOT__regs
                                    [0x19U];
                            }(), __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout));
                VL_WRITEF("Register 26: %016x\n",64,
                          ([&]() {
                                __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout 
                                    = vlSelf->top__DOT__registers__DOT__regs
                                    [0x1aU];
                            }(), __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout));
                VL_WRITEF("Register 27: %016x\n",64,
                          ([&]() {
                                __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout 
                                    = vlSelf->top__DOT__registers__DOT__regs
                                    [0x1bU];
                            }(), __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout));
                VL_WRITEF("Register 28: %016x\n",64,
                          ([&]() {
                                __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout 
                                    = vlSelf->top__DOT__registers__DOT__regs
                                    [0x1cU];
                            }(), __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout));
                VL_WRITEF("Register 29: %016x\n",64,
                          ([&]() {
                                __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout 
                                    = vlSelf->top__DOT__registers__DOT__regs
                                    [0x1dU];
                            }(), __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout));
                VL_WRITEF("Register 30: %016x\n",64,
                          ([&]() {
                                __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout 
                                    = vlSelf->top__DOT__registers__DOT__regs
                                    [0x1eU];
                            }(), __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout));
                VL_WRITEF("Register 31: %016x\n",64,
                          ([&]() {
                                __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout 
                                    = vlSelf->top__DOT__registers__DOT__regs
                                    [0x1fU];
                            }(), __Vfunc_top__DOT__registers__DOT__read_reg__0__Vfuncout));
                VL_FINISH_MT("top.sv", 903, "");
            } else {
                if (vlSelf->top__DOT__has_rd) {
                    __Vtemp_1 = ([&]() {
                            __Vfunc_top__DOT__codeword_text__1__value 
                                = vlSelf->top__DOT__codeword;
                            {
                                if ((0x40U == (IData)(__Vfunc_top__DOT__codeword_text__1__value))) {
                                    __Vfunc_top__DOT__codeword_text__1__Vfuncout = 
                                        std::string{"FENCE.I"};
                                    goto __Vlabel1;
                                }
                                __Vfunc_top__DOT__codeword_text__1__Vfuncout 
                                    = Vtop___024unit::__Venumtab_enum_name0
                                    .at((IData)(__Vfunc_top__DOT__codeword_text__1__value));
                                __Vlabel1: ;
                            }
                        }(), __Vfunc_top__DOT__codeword_text__1__Vfuncout);
                    VL_WRITEF("%x: %@ %0#\n",64,vlSelf->top__DOT__pc,
                              -1,&(__Vtemp_1),5,(0x1fU 
                                                 & (vlSelf->top__DOT__instr 
                                                    >> 7U)));
                } else {
                    __Vtemp_2 = ([&]() {
                            __Vfunc_top__DOT__codeword_text__2__value 
                                = vlSelf->top__DOT__codeword;
                            {
                                if ((0x40U == (IData)(__Vfunc_top__DOT__codeword_text__2__value))) {
                                    __Vfunc_top__DOT__codeword_text__2__Vfuncout = 
                                        std::string{"FENCE.I"};
                                    goto __Vlabel2;
                                }
                                __Vfunc_top__DOT__codeword_text__2__Vfuncout 
                                    = Vtop___024unit::__Venumtab_enum_name0
                                    .at((IData)(__Vfunc_top__DOT__codeword_text__2__value));
                                __Vlabel2: ;
                            }
                        }(), __Vfunc_top__DOT__codeword_text__2__Vfuncout);
                    VL_WRITEF("%x: %@\n",64,vlSelf->top__DOT__pc,
                              -1,&(__Vtemp_2));
                }
                __Vdly__top__DOT__pc = vlSelf->top__DOT__next_pc;
            }
            __Vdly__top__DOT__state = 1U;
        } else if (vlSelf->m_axi_rvalid) {
            VL_ASSIGNSEL_WQ(512,64,(0x1ffU & VL_SHIFTL_III(9,32,32, (IData)(vlSelf->top__DOT__beat_count), 6U)), vlSelf->top__DOT__fetched_line, vlSelf->m_axi_rdata);
            if (vlSelf->m_axi_rlast) {
                __Vdly__top__DOT__state = 3U;
            } else {
                __Vdly__top__DOT__beat_count = (7U 
                                                & ((IData)(1U) 
                                                   + (IData)(vlSelf->top__DOT__beat_count)));
            }
        }
    } else if ((1U & (IData)(vlSelf->top__DOT__state))) {
        if (((IData)(vlSelf->m_axi_arvalid) & (IData)(vlSelf->m_axi_arready))) {
            __Vdly__top__DOT__beat_count = 0U;
            __Vdly__top__DOT__state = 2U;
        }
    } else {
        __Vdly__top__DOT__state = 1U;
    }
    vlSelf->top__DOT__beat_count = __Vdly__top__DOT__beat_count;
    vlSelf->top__DOT__state = __Vdly__top__DOT__state;
    if (__Vdlyvset__top__DOT__registers__DOT__regs__v0) {
        vlSelf->top__DOT__registers__DOT__regs[0U] = 0ULL;
        vlSelf->top__DOT__registers__DOT__regs[1U] = 0ULL;
        vlSelf->top__DOT__registers__DOT__regs[2U] = 0ULL;
        vlSelf->top__DOT__registers__DOT__regs[3U] = 0ULL;
        vlSelf->top__DOT__registers__DOT__regs[4U] = 0ULL;
        vlSelf->top__DOT__registers__DOT__regs[5U] = 0ULL;
        vlSelf->top__DOT__registers__DOT__regs[6U] = 0ULL;
        vlSelf->top__DOT__registers__DOT__regs[7U] = 0ULL;
        vlSelf->top__DOT__registers__DOT__regs[8U] = 0ULL;
        vlSelf->top__DOT__registers__DOT__regs[9U] = 0ULL;
        vlSelf->top__DOT__registers__DOT__regs[0xaU] = 0ULL;
        vlSelf->top__DOT__registers__DOT__regs[0xbU] = 0ULL;
        vlSelf->top__DOT__registers__DOT__regs[0xcU] = 0ULL;
        vlSelf->top__DOT__registers__DOT__regs[0xdU] = 0ULL;
        vlSelf->top__DOT__registers__DOT__regs[0xeU] = 0ULL;
        vlSelf->top__DOT__registers__DOT__regs[0xfU] = 0ULL;
        vlSelf->top__DOT__registers__DOT__regs[0x10U] = 0ULL;
        vlSelf->top__DOT__registers__DOT__regs[0x11U] = 0ULL;
        vlSelf->top__DOT__registers__DOT__regs[0x12U] = 0ULL;
        vlSelf->top__DOT__registers__DOT__regs[0x13U] = 0ULL;
        vlSelf->top__DOT__registers__DOT__regs[0x14U] = 0ULL;
        vlSelf->top__DOT__registers__DOT__regs[0x15U] = 0ULL;
        vlSelf->top__DOT__registers__DOT__regs[0x16U] = 0ULL;
        vlSelf->top__DOT__registers__DOT__regs[0x17U] = 0ULL;
        vlSelf->top__DOT__registers__DOT__regs[0x18U] = 0ULL;
        vlSelf->top__DOT__registers__DOT__regs[0x19U] = 0ULL;
        vlSelf->top__DOT__registers__DOT__regs[0x1aU] = 0ULL;
        vlSelf->top__DOT__registers__DOT__regs[0x1bU] = 0ULL;
        vlSelf->top__DOT__registers__DOT__regs[0x1cU] = 0ULL;
        vlSelf->top__DOT__registers__DOT__regs[0x1dU] = 0ULL;
        vlSelf->top__DOT__registers__DOT__regs[0x1eU] = 0ULL;
        vlSelf->top__DOT__registers__DOT__regs[0x1fU] = 0ULL;
        vlSelf->top__DOT__registers__DOT__regs[2U] 
            = __Vdlyvval__top__DOT__registers__DOT__regs__v32;
    }
    if (__Vdlyvset__top__DOT__registers__DOT__regs__v33) {
        vlSelf->top__DOT__registers__DOT__regs[__Vdlyvdim0__top__DOT__registers__DOT__regs__v33] 
            = __Vdlyvval__top__DOT__registers__DOT__regs__v33;
    }
    vlSelf->top__DOT__pc = __Vdly__top__DOT__pc;
    vlSelf->m_axi_arvalid = (1U == (IData)(vlSelf->top__DOT__state));
    vlSelf->m_axi_rready = (2U == (IData)(vlSelf->top__DOT__state));
    vlSelf->m_axi_araddr = (0xffffffffffffffc0ULL & vlSelf->top__DOT__pc);
    vlSelf->top__DOT__next_pc = (4ULL + vlSelf->top__DOT__pc);
    vlSelf->top__DOT__instr = (((0U == (0x1fU & VL_SHIFTL_III(9,9,32, 
                                                              (0xfU 
                                                               & (IData)(
                                                                         (vlSelf->top__DOT__pc 
                                                                          >> 2U))), 5U)))
                                 ? 0U : (vlSelf->top__DOT__fetched_line[
                                         (((IData)(0x1fU) 
                                           + (0x1ffU 
                                              & VL_SHIFTL_III(9,9,32, 
                                                              (0xfU 
                                                               & (IData)(
                                                                         (vlSelf->top__DOT__pc 
                                                                          >> 2U))), 5U))) 
                                          >> 5U)] << 
                                         ((IData)(0x20U) 
                                          - (0x1fU 
                                             & VL_SHIFTL_III(9,9,32, 
                                                             (0xfU 
                                                              & (IData)(
                                                                        (vlSelf->top__DOT__pc 
                                                                         >> 2U))), 5U))))) 
                               | (vlSelf->top__DOT__fetched_line[
                                  (0xfU & (VL_SHIFTL_III(9,9,32, 
                                                         (0xfU 
                                                          & (IData)(
                                                                    (vlSelf->top__DOT__pc 
                                                                     >> 2U))), 5U) 
                                           >> 5U))] 
                                  >> (0x1fU & VL_SHIFTL_III(9,9,32, 
                                                            (0xfU 
                                                             & (IData)(
                                                                       (vlSelf->top__DOT__pc 
                                                                        >> 2U))), 5U))));
    top__DOT____VdfgExtracted_h6b31312d__0 = (((QData)((IData)(
                                                               (- (IData)(
                                                                          (vlSelf->top__DOT__instr 
                                                                           >> 0x1fU))))) 
                                               << 0x20U) 
                                              | (QData)((IData)(
                                                                (0xfffff000U 
                                                                 & vlSelf->top__DOT__instr))));
    top__DOT__decode__DOT__opcode = (0x7fU & vlSelf->top__DOT__instr);
    top__DOT__decode__DOT__funct3 = (7U & (vlSelf->top__DOT__instr 
                                           >> 0xcU));
    top__DOT__decode__DOT__funct7 = (vlSelf->top__DOT__instr 
                                     >> 0x19U);
    vlSelf->top__DOT__has_rd = 0U;
    vlSelf->top__DOT__codeword = 0U;
    if ((3U != (3U & vlSelf->top__DOT__instr))) {
        vlSelf->top__DOT__codeword = 0U;
        vlSelf->top__DOT__has_rd = 0U;
    }
    if ((0x40U & (IData)(top__DOT__decode__DOT__opcode))) {
        if ((0x20U & (IData)(top__DOT__decode__DOT__opcode))) {
            if ((0x10U & (IData)(top__DOT__decode__DOT__opcode))) {
                if ((8U & (IData)(top__DOT__decode__DOT__opcode))) {
                    vlSelf->top__DOT__codeword = 0U;
                    vlSelf->top__DOT__has_rd = 0U;
                } else if ((4U & (IData)(top__DOT__decode__DOT__opcode))) {
                    vlSelf->top__DOT__codeword = 0U;
                    vlSelf->top__DOT__has_rd = 0U;
                } else if ((0x73U == vlSelf->top__DOT__instr)) {
                    vlSelf->top__DOT__codeword = 0x41U;
                    vlSelf->top__DOT__has_rd = 0U;
                } else if ((0x100073U == vlSelf->top__DOT__instr)) {
                    vlSelf->top__DOT__codeword = 0x42U;
                    vlSelf->top__DOT__has_rd = 0U;
                } else {
                    vlSelf->top__DOT__has_rd = 1U;
                    if ((4U & (IData)(top__DOT__decode__DOT__funct3))) {
                        if ((2U & (IData)(top__DOT__decode__DOT__funct3))) {
                            vlSelf->top__DOT__codeword 
                                = ((1U & (IData)(top__DOT__decode__DOT__funct3))
                                    ? 0x48U : 0x47U);
                        } else if ((1U & (IData)(top__DOT__decode__DOT__funct3))) {
                            vlSelf->top__DOT__codeword = 0x46U;
                        } else {
                            vlSelf->top__DOT__codeword = 0U;
                            vlSelf->top__DOT__has_rd = 0U;
                        }
                    } else if ((2U & (IData)(top__DOT__decode__DOT__funct3))) {
                        vlSelf->top__DOT__codeword 
                            = ((1U & (IData)(top__DOT__decode__DOT__funct3))
                                ? 0x45U : 0x44U);
                    } else if ((1U & (IData)(top__DOT__decode__DOT__funct3))) {
                        vlSelf->top__DOT__codeword = 0x43U;
                    } else {
                        vlSelf->top__DOT__codeword = 0U;
                        vlSelf->top__DOT__has_rd = 0U;
                    }
                }
            } else if ((8U & (IData)(top__DOT__decode__DOT__opcode))) {
                if ((4U & (IData)(top__DOT__decode__DOT__opcode))) {
                    vlSelf->top__DOT__codeword = 3U;
                    vlSelf->top__DOT__has_rd = 1U;
                } else {
                    vlSelf->top__DOT__codeword = 0U;
                    vlSelf->top__DOT__has_rd = 0U;
                }
            } else if ((4U & (IData)(top__DOT__decode__DOT__opcode))) {
                if ((0U == (IData)(top__DOT__decode__DOT__funct3))) {
                    vlSelf->top__DOT__codeword = 4U;
                    vlSelf->top__DOT__has_rd = 1U;
                } else {
                    vlSelf->top__DOT__codeword = 0U;
                    vlSelf->top__DOT__has_rd = 0U;
                }
            } else {
                vlSelf->top__DOT__has_rd = 0U;
                vlSelf->top__DOT__codeword = ((4U & (IData)(top__DOT__decode__DOT__funct3))
                                               ? ((2U 
                                                   & (IData)(top__DOT__decode__DOT__funct3))
                                                   ? 
                                                  ((1U 
                                                    & (IData)(top__DOT__decode__DOT__funct3))
                                                    ? 0xaU
                                                    : 9U)
                                                   : 
                                                  ((1U 
                                                    & (IData)(top__DOT__decode__DOT__funct3))
                                                    ? 8U
                                                    : 7U))
                                               : ((2U 
                                                   & (IData)(top__DOT__decode__DOT__funct3))
                                                   ? 0U
                                                   : 
                                                  ((1U 
                                                    & (IData)(top__DOT__decode__DOT__funct3))
                                                    ? 6U
                                                    : 5U)));
            }
        } else {
            vlSelf->top__DOT__codeword = 0U;
            vlSelf->top__DOT__has_rd = 0U;
        }
    } else if ((0x20U & (IData)(top__DOT__decode__DOT__opcode))) {
        if ((0x10U & (IData)(top__DOT__decode__DOT__opcode))) {
            if ((8U & (IData)(top__DOT__decode__DOT__opcode))) {
                if ((4U & (IData)(top__DOT__decode__DOT__opcode))) {
                    vlSelf->top__DOT__codeword = 0U;
                    vlSelf->top__DOT__has_rd = 0U;
                } else {
                    vlSelf->top__DOT__has_rd = 1U;
                    if ((1U != (IData)(top__DOT__decode__DOT__funct7))) {
                        if ((0U == (IData)(top__DOT__decode__DOT__funct3))) {
                            if ((0U == (IData)(top__DOT__decode__DOT__funct7))) {
                                vlSelf->top__DOT__codeword = 0x35U;
                            } else if ((0x20U == (IData)(top__DOT__decode__DOT__funct7))) {
                                vlSelf->top__DOT__codeword = 0x36U;
                            } else {
                                vlSelf->top__DOT__codeword = 0U;
                                vlSelf->top__DOT__has_rd = 0U;
                            }
                        } else if ((1U == (IData)(top__DOT__decode__DOT__funct3))) {
                            if ((0U == (IData)(top__DOT__decode__DOT__funct7))) {
                                vlSelf->top__DOT__codeword = 0x37U;
                            } else {
                                vlSelf->top__DOT__codeword = 0U;
                                vlSelf->top__DOT__has_rd = 0U;
                            }
                        } else if ((5U == (IData)(top__DOT__decode__DOT__funct3))) {
                            if ((0U == (IData)(top__DOT__decode__DOT__funct7))) {
                                vlSelf->top__DOT__codeword = 0x38U;
                            } else if ((0x20U == (IData)(top__DOT__decode__DOT__funct7))) {
                                vlSelf->top__DOT__codeword = 0x39U;
                            } else {
                                vlSelf->top__DOT__codeword = 0U;
                                vlSelf->top__DOT__has_rd = 0U;
                            }
                        } else {
                            vlSelf->top__DOT__codeword = 0U;
                            vlSelf->top__DOT__has_rd = 0U;
                        }
                    } else if ((4U & (IData)(top__DOT__decode__DOT__funct3))) {
                        vlSelf->top__DOT__codeword 
                            = ((2U & (IData)(top__DOT__decode__DOT__funct3))
                                ? ((1U & (IData)(top__DOT__decode__DOT__funct3))
                                    ? 0x3eU : 0x3dU)
                                : ((1U & (IData)(top__DOT__decode__DOT__funct3))
                                    ? 0x3cU : 0x3bU));
                    } else if ((2U & (IData)(top__DOT__decode__DOT__funct3))) {
                        vlSelf->top__DOT__codeword = 0U;
                        vlSelf->top__DOT__has_rd = 0U;
                    } else if ((1U & (IData)(top__DOT__decode__DOT__funct3))) {
                        vlSelf->top__DOT__codeword = 0U;
                        vlSelf->top__DOT__has_rd = 0U;
                    } else {
                        vlSelf->top__DOT__codeword = 0x3aU;
                    }
                }
            } else if ((4U & (IData)(top__DOT__decode__DOT__opcode))) {
                vlSelf->top__DOT__codeword = 1U;
                vlSelf->top__DOT__has_rd = 1U;
            } else {
                vlSelf->top__DOT__has_rd = 1U;
                if ((1U != (IData)(top__DOT__decode__DOT__funct7))) {
                    if ((4U & (IData)(top__DOT__decode__DOT__funct3))) {
                        if ((2U & (IData)(top__DOT__decode__DOT__funct3))) {
                            if ((1U & (IData)(top__DOT__decode__DOT__funct3))) {
                                if ((0U == (IData)(top__DOT__decode__DOT__funct7))) {
                                    vlSelf->top__DOT__codeword = 0x28U;
                                } else {
                                    vlSelf->top__DOT__codeword = 0U;
                                    vlSelf->top__DOT__has_rd = 0U;
                                }
                            } else if ((0U == (IData)(top__DOT__decode__DOT__funct7))) {
                                vlSelf->top__DOT__codeword = 0x27U;
                            } else {
                                vlSelf->top__DOT__codeword = 0U;
                                vlSelf->top__DOT__has_rd = 0U;
                            }
                        } else if ((1U & (IData)(top__DOT__decode__DOT__funct3))) {
                            if ((0U == (IData)(top__DOT__decode__DOT__funct7))) {
                                vlSelf->top__DOT__codeword = 0x25U;
                            } else if ((0x20U == (IData)(top__DOT__decode__DOT__funct7))) {
                                vlSelf->top__DOT__codeword = 0x26U;
                            } else {
                                vlSelf->top__DOT__codeword = 0U;
                                vlSelf->top__DOT__has_rd = 0U;
                            }
                        } else if ((0U == (IData)(top__DOT__decode__DOT__funct7))) {
                            vlSelf->top__DOT__codeword = 0x24U;
                        } else {
                            vlSelf->top__DOT__codeword = 0U;
                            vlSelf->top__DOT__has_rd = 0U;
                        }
                    } else if ((2U & (IData)(top__DOT__decode__DOT__funct3))) {
                        if ((1U & (IData)(top__DOT__decode__DOT__funct3))) {
                            if ((0U == (IData)(top__DOT__decode__DOT__funct7))) {
                                vlSelf->top__DOT__codeword = 0x23U;
                            } else {
                                vlSelf->top__DOT__codeword = 0U;
                                vlSelf->top__DOT__has_rd = 0U;
                            }
                        } else if ((0U == (IData)(top__DOT__decode__DOT__funct7))) {
                            vlSelf->top__DOT__codeword = 0x22U;
                        } else {
                            vlSelf->top__DOT__codeword = 0U;
                            vlSelf->top__DOT__has_rd = 0U;
                        }
                    } else if ((1U & (IData)(top__DOT__decode__DOT__funct3))) {
                        if ((0U == (IData)(top__DOT__decode__DOT__funct7))) {
                            vlSelf->top__DOT__codeword = 0x21U;
                        } else {
                            vlSelf->top__DOT__codeword = 0U;
                            vlSelf->top__DOT__has_rd = 0U;
                        }
                    } else if ((0U == (IData)(top__DOT__decode__DOT__funct7))) {
                        vlSelf->top__DOT__codeword = 0x1fU;
                    } else if ((0x20U == (IData)(top__DOT__decode__DOT__funct7))) {
                        vlSelf->top__DOT__codeword = 0x20U;
                    } else {
                        vlSelf->top__DOT__codeword = 0U;
                        vlSelf->top__DOT__has_rd = 0U;
                    }
                } else {
                    vlSelf->top__DOT__codeword = ((4U 
                                                   & (IData)(top__DOT__decode__DOT__funct3))
                                                   ? 
                                                  ((2U 
                                                    & (IData)(top__DOT__decode__DOT__funct3))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(top__DOT__decode__DOT__funct3))
                                                     ? 0x30U
                                                     : 0x2fU)
                                                    : 
                                                   ((1U 
                                                     & (IData)(top__DOT__decode__DOT__funct3))
                                                     ? 0x2eU
                                                     : 0x2dU))
                                                   : 
                                                  ((2U 
                                                    & (IData)(top__DOT__decode__DOT__funct3))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(top__DOT__decode__DOT__funct3))
                                                     ? 0x2cU
                                                     : 0x2bU)
                                                    : 
                                                   ((1U 
                                                     & (IData)(top__DOT__decode__DOT__funct3))
                                                     ? 0x2aU
                                                     : 0x29U)));
                }
            }
        } else if ((8U & (IData)(top__DOT__decode__DOT__opcode))) {
            vlSelf->top__DOT__codeword = 0U;
            vlSelf->top__DOT__has_rd = 0U;
        } else if ((4U & (IData)(top__DOT__decode__DOT__opcode))) {
            vlSelf->top__DOT__codeword = 0U;
            vlSelf->top__DOT__has_rd = 0U;
        } else {
            vlSelf->top__DOT__has_rd = 0U;
            vlSelf->top__DOT__codeword = ((4U & (IData)(top__DOT__decode__DOT__funct3))
                                           ? 0U : (
                                                   (2U 
                                                    & (IData)(top__DOT__decode__DOT__funct3))
                                                    ? 
                                                   ((1U 
                                                     & (IData)(top__DOT__decode__DOT__funct3))
                                                     ? 0x15U
                                                     : 0x14U)
                                                    : 
                                                   ((1U 
                                                     & (IData)(top__DOT__decode__DOT__funct3))
                                                     ? 0x13U
                                                     : 0x12U)));
        }
    } else if ((0x10U & (IData)(top__DOT__decode__DOT__opcode))) {
        if ((8U & (IData)(top__DOT__decode__DOT__opcode))) {
            if ((4U & (IData)(top__DOT__decode__DOT__opcode))) {
                vlSelf->top__DOT__codeword = 0U;
                vlSelf->top__DOT__has_rd = 0U;
            } else {
                vlSelf->top__DOT__has_rd = 1U;
                if ((0U == (IData)(top__DOT__decode__DOT__funct3))) {
                    vlSelf->top__DOT__codeword = 0x31U;
                } else if ((1U == (IData)(top__DOT__decode__DOT__funct3))) {
                    if ((0U == (IData)(top__DOT__decode__DOT__funct7))) {
                        vlSelf->top__DOT__codeword = 0x32U;
                    } else {
                        vlSelf->top__DOT__codeword = 0U;
                        vlSelf->top__DOT__has_rd = 0U;
                    }
                } else if ((5U == (IData)(top__DOT__decode__DOT__funct3))) {
                    if ((0U == (IData)(top__DOT__decode__DOT__funct7))) {
                        vlSelf->top__DOT__codeword = 0x33U;
                    } else if ((0x20U == (IData)(top__DOT__decode__DOT__funct7))) {
                        vlSelf->top__DOT__codeword = 0x34U;
                    } else {
                        vlSelf->top__DOT__codeword = 0U;
                        vlSelf->top__DOT__has_rd = 0U;
                    }
                } else {
                    vlSelf->top__DOT__codeword = 0U;
                    vlSelf->top__DOT__has_rd = 0U;
                }
            }
        } else if ((4U & (IData)(top__DOT__decode__DOT__opcode))) {
            vlSelf->top__DOT__codeword = 2U;
            vlSelf->top__DOT__has_rd = 1U;
        } else {
            vlSelf->top__DOT__has_rd = 1U;
            if ((4U & (IData)(top__DOT__decode__DOT__funct3))) {
                if ((2U & (IData)(top__DOT__decode__DOT__funct3))) {
                    vlSelf->top__DOT__codeword = ((1U 
                                                   & (IData)(top__DOT__decode__DOT__funct3))
                                                   ? 0x1bU
                                                   : 0x1aU);
                } else if ((1U & (IData)(top__DOT__decode__DOT__funct3))) {
                    if ((0U == (0x3fU & ((IData)(top__DOT__decode__DOT__funct7) 
                                         >> 1U)))) {
                        vlSelf->top__DOT__codeword = 0x1dU;
                    } else if ((0x10U == (0x3fU & ((IData)(top__DOT__decode__DOT__funct7) 
                                                   >> 1U)))) {
                        vlSelf->top__DOT__codeword = 0x1eU;
                    } else {
                        vlSelf->top__DOT__codeword = 0U;
                        vlSelf->top__DOT__has_rd = 0U;
                    }
                } else {
                    vlSelf->top__DOT__codeword = 0x19U;
                }
            } else if ((2U & (IData)(top__DOT__decode__DOT__funct3))) {
                vlSelf->top__DOT__codeword = ((1U & (IData)(top__DOT__decode__DOT__funct3))
                                               ? 0x18U
                                               : 0x17U);
            } else if ((1U & (IData)(top__DOT__decode__DOT__funct3))) {
                if ((0U == (0x3fU & ((IData)(top__DOT__decode__DOT__funct7) 
                                     >> 1U)))) {
                    vlSelf->top__DOT__codeword = 0x1cU;
                } else {
                    vlSelf->top__DOT__codeword = 0U;
                    vlSelf->top__DOT__has_rd = 0U;
                }
            } else {
                vlSelf->top__DOT__codeword = 0x16U;
            }
        }
    } else if ((8U & (IData)(top__DOT__decode__DOT__opcode))) {
        if ((4U & (IData)(top__DOT__decode__DOT__opcode))) {
            vlSelf->top__DOT__has_rd = 0U;
            vlSelf->top__DOT__codeword = ((0U == (IData)(top__DOT__decode__DOT__funct3))
                                           ? 0x3fU : 
                                          ((1U == (IData)(top__DOT__decode__DOT__funct3))
                                            ? 0x40U
                                            : 0U));
        } else {
            vlSelf->top__DOT__codeword = 0U;
            vlSelf->top__DOT__has_rd = 0U;
        }
    } else if ((4U & (IData)(top__DOT__decode__DOT__opcode))) {
        vlSelf->top__DOT__codeword = 0U;
        vlSelf->top__DOT__has_rd = 0U;
    } else {
        vlSelf->top__DOT__has_rd = 1U;
        if ((4U & (IData)(top__DOT__decode__DOT__funct3))) {
            if ((2U & (IData)(top__DOT__decode__DOT__funct3))) {
                if ((1U & (IData)(top__DOT__decode__DOT__funct3))) {
                    vlSelf->top__DOT__codeword = 0U;
                    vlSelf->top__DOT__has_rd = 0U;
                } else {
                    vlSelf->top__DOT__codeword = 0x10U;
                }
            } else {
                vlSelf->top__DOT__codeword = ((1U & (IData)(top__DOT__decode__DOT__funct3))
                                               ? 0xfU
                                               : 0xeU);
            }
        } else {
            vlSelf->top__DOT__codeword = ((2U & (IData)(top__DOT__decode__DOT__funct3))
                                           ? ((1U & (IData)(top__DOT__decode__DOT__funct3))
                                               ? 0x11U
                                               : 0xdU)
                                           : ((1U & (IData)(top__DOT__decode__DOT__funct3))
                                               ? 0xcU
                                               : 0xbU));
        }
    }
    top__DOT__alu_a = ((0U == (0x1fU & (vlSelf->top__DOT__instr 
                                        >> 0xfU))) ? 0ULL
                        : vlSelf->top__DOT__registers__DOT__regs
                       [(0x1fU & (vlSelf->top__DOT__instr 
                                  >> 0xfU))]);
    top__DOT__immediate = (((- (QData)((IData)((vlSelf->top__DOT__instr 
                                                >> 0x1fU)))) 
                            << 0xcU) | (QData)((IData)(
                                                       (vlSelf->top__DOT__instr 
                                                        >> 0x14U))));
    top__DOT__alu_b = ((0U == (0x1fU & (vlSelf->top__DOT__instr 
                                        >> 0x14U)))
                        ? 0ULL : vlSelf->top__DOT__registers__DOT__regs
                       [(0x1fU & (vlSelf->top__DOT__instr 
                                  >> 0x14U))]);
    if ((1U & (~ ((IData)(vlSelf->top__DOT__codeword) 
                  >> 6U)))) {
        if ((1U & (~ ((IData)(vlSelf->top__DOT__codeword) 
                      >> 5U)))) {
            if ((1U & (~ ((IData)(vlSelf->top__DOT__codeword) 
                          >> 4U)))) {
                if ((1U & (~ ((IData)(vlSelf->top__DOT__codeword) 
                              >> 3U)))) {
                    if ((1U & (~ ((IData)(vlSelf->top__DOT__codeword) 
                                  >> 2U)))) {
                        if ((2U & (IData)(vlSelf->top__DOT__codeword))) {
                            if ((1U & (~ (IData)(vlSelf->top__DOT__codeword)))) {
                                top__DOT__alu_a = vlSelf->top__DOT__pc;
                            }
                        }
                    }
                }
            }
        }
        if ((0x20U & (IData)(vlSelf->top__DOT__codeword))) {
            if ((0x10U & (IData)(vlSelf->top__DOT__codeword))) {
                if ((1U & (~ ((IData)(vlSelf->top__DOT__codeword) 
                              >> 3U)))) {
                    if ((4U & (IData)(vlSelf->top__DOT__codeword))) {
                        if ((1U & (~ ((IData)(vlSelf->top__DOT__codeword) 
                                      >> 1U)))) {
                            if ((1U & (~ (IData)(vlSelf->top__DOT__codeword)))) {
                                top__DOT__alu_b = (QData)((IData)(
                                                                  (0x1fU 
                                                                   & (vlSelf->top__DOT__instr 
                                                                      >> 0x14U))));
                            }
                        }
                    } else if ((2U & (IData)(vlSelf->top__DOT__codeword))) {
                        top__DOT__alu_b = (QData)((IData)(
                                                          (0x1fU 
                                                           & (vlSelf->top__DOT__instr 
                                                              >> 0x14U))));
                    } else if ((1U & (IData)(vlSelf->top__DOT__codeword))) {
                        top__DOT__alu_b = top__DOT__immediate;
                    }
                }
            }
        } else if ((0x10U & (IData)(vlSelf->top__DOT__codeword))) {
            if ((8U & (IData)(vlSelf->top__DOT__codeword))) {
                if ((4U & (IData)(vlSelf->top__DOT__codeword))) {
                    if ((2U & (IData)(vlSelf->top__DOT__codeword))) {
                        if ((1U & (~ (IData)(vlSelf->top__DOT__codeword)))) {
                            top__DOT__alu_b = (QData)((IData)(
                                                              (0x3fU 
                                                               & (vlSelf->top__DOT__instr 
                                                                  >> 0x14U))));
                        }
                    } else {
                        top__DOT__alu_b = (QData)((IData)(
                                                          (0x3fU 
                                                           & (vlSelf->top__DOT__instr 
                                                              >> 0x14U))));
                    }
                } else {
                    top__DOT__alu_b = top__DOT__immediate;
                }
            } else if ((4U & (IData)(vlSelf->top__DOT__codeword))) {
                if ((2U & (IData)(vlSelf->top__DOT__codeword))) {
                    top__DOT__alu_b = top__DOT__immediate;
                }
            }
        } else if ((1U & (~ ((IData)(vlSelf->top__DOT__codeword) 
                             >> 3U)))) {
            if ((1U & (~ ((IData)(vlSelf->top__DOT__codeword) 
                          >> 2U)))) {
                if ((2U & (IData)(vlSelf->top__DOT__codeword))) {
                    if ((1U & (~ (IData)(vlSelf->top__DOT__codeword)))) {
                        top__DOT__immediate = top__DOT____VdfgExtracted_h6b31312d__0;
                        top__DOT__alu_b = top__DOT__immediate;
                    }
                } else if ((1U & (IData)(vlSelf->top__DOT__codeword))) {
                    top__DOT__immediate = top__DOT____VdfgExtracted_h6b31312d__0;
                    top__DOT__alu_b = top__DOT__immediate;
                }
            }
        }
    }
    vlSelf->top__DOT__alu_result = 0ULL;
    top__DOT__execute_alu__DOT__word_result = 0U;
    __Vtemp_3[0U] = (IData)(top__DOT__alu_a);
    __Vtemp_3[1U] = (IData)((top__DOT__alu_a >> 0x20U));
    __Vtemp_3[2U] = (IData)((- (QData)((IData)((1U 
                                                & (IData)(
                                                          (top__DOT__alu_a 
                                                           >> 0x3fU)))))));
    __Vtemp_3[3U] = (IData)(((- (QData)((IData)((1U 
                                                 & (IData)(
                                                           (top__DOT__alu_a 
                                                            >> 0x3fU)))))) 
                             >> 0x20U));
    __Vtemp_4[0U] = (IData)(top__DOT__alu_b);
    __Vtemp_4[1U] = (IData)((top__DOT__alu_b >> 0x20U));
    __Vtemp_4[2U] = (IData)((- (QData)((IData)((1U 
                                                & (IData)(
                                                          (top__DOT__alu_b 
                                                           >> 0x3fU)))))));
    __Vtemp_4[3U] = (IData)(((- (QData)((IData)((1U 
                                                 & (IData)(
                                                           (top__DOT__alu_b 
                                                            >> 0x3fU)))))) 
                             >> 0x20U));
    VL_MULS_WWW(128, top__DOT__execute_alu__DOT__signed_product, __Vtemp_3, __Vtemp_4);
    __Vtemp_5[0U] = (IData)(top__DOT__alu_a);
    __Vtemp_5[1U] = (IData)((top__DOT__alu_a >> 0x20U));
    __Vtemp_5[2U] = (IData)((- (QData)((IData)((1U 
                                                & (IData)(
                                                          (top__DOT__alu_a 
                                                           >> 0x3fU)))))));
    __Vtemp_5[3U] = (IData)(((- (QData)((IData)((1U 
                                                 & (IData)(
                                                           (top__DOT__alu_a 
                                                            >> 0x3fU)))))) 
                             >> 0x20U));
    __Vtemp_6[0U] = (IData)(top__DOT__alu_b);
    __Vtemp_6[1U] = (IData)((top__DOT__alu_b >> 0x20U));
    __Vtemp_6[2U] = 0U;
    __Vtemp_6[3U] = 0U;
    VL_MULS_WWW(128, top__DOT__execute_alu__DOT__signed_unsigned_product, __Vtemp_5, __Vtemp_6);
    __Vtemp_7[0U] = (IData)(top__DOT__alu_a);
    __Vtemp_7[1U] = (IData)((top__DOT__alu_a >> 0x20U));
    __Vtemp_7[2U] = 0U;
    __Vtemp_7[3U] = 0U;
    __Vtemp_8[0U] = (IData)(top__DOT__alu_b);
    __Vtemp_8[1U] = (IData)((top__DOT__alu_b >> 0x20U));
    __Vtemp_8[2U] = 0U;
    __Vtemp_8[3U] = 0U;
    VL_MUL_W(4, top__DOT__execute_alu__DOT__unsigned_product, __Vtemp_7, __Vtemp_8);
    if ((0x40U & (IData)(vlSelf->top__DOT__codeword))) {
        vlSelf->top__DOT__alu_result = 0ULL;
    } else if ((0x20U & (IData)(vlSelf->top__DOT__codeword))) {
        if ((0x10U & (IData)(vlSelf->top__DOT__codeword))) {
            if ((8U & (IData)(vlSelf->top__DOT__codeword))) {
                if ((4U & (IData)(vlSelf->top__DOT__codeword))) {
                    if ((2U & (IData)(vlSelf->top__DOT__codeword))) {
                        if ((1U & (IData)(vlSelf->top__DOT__codeword))) {
                            vlSelf->top__DOT__alu_result = 0ULL;
                        } else if ((0U == (IData)(top__DOT__alu_b))) {
                            vlSelf->top__DOT__alu_result 
                                = (((QData)((IData)(
                                                    (- (IData)(
                                                               (1U 
                                                                & (IData)(
                                                                          (top__DOT__alu_a 
                                                                           >> 0x1fU))))))) 
                                    << 0x20U) | (QData)((IData)(top__DOT__alu_a)));
                        } else {
                            top__DOT__execute_alu__DOT__word_result 
                                = VL_MODDIV_III(32, (IData)(top__DOT__alu_a), (IData)(top__DOT__alu_b));
                            vlSelf->top__DOT__alu_result 
                                = (((QData)((IData)(
                                                    (- (IData)(
                                                               (top__DOT__execute_alu__DOT__word_result 
                                                                >> 0x1fU))))) 
                                    << 0x20U) | (QData)((IData)(top__DOT__execute_alu__DOT__word_result)));
                        }
                    } else if ((1U & (IData)(vlSelf->top__DOT__codeword))) {
                        if ((0U == (IData)(top__DOT__alu_b))) {
                            vlSelf->top__DOT__alu_result 
                                = (((QData)((IData)(
                                                    (- (IData)(
                                                               (1U 
                                                                & (IData)(
                                                                          (top__DOT__alu_a 
                                                                           >> 0x1fU))))))) 
                                    << 0x20U) | (QData)((IData)(top__DOT__alu_a)));
                        } else if (((0x80000000U == (IData)(top__DOT__alu_a)) 
                                    & (0xffffffffU 
                                       == (IData)(top__DOT__alu_b)))) {
                            vlSelf->top__DOT__alu_result = 0ULL;
                        } else {
                            top__DOT__execute_alu__DOT__word_result 
                                = VL_MODDIVS_III(32, (IData)(top__DOT__alu_a), (IData)(top__DOT__alu_b));
                            vlSelf->top__DOT__alu_result 
                                = (((QData)((IData)(
                                                    (- (IData)(
                                                               (top__DOT__execute_alu__DOT__word_result 
                                                                >> 0x1fU))))) 
                                    << 0x20U) | (QData)((IData)(top__DOT__execute_alu__DOT__word_result)));
                        }
                    } else if ((0U == (IData)(top__DOT__alu_b))) {
                        vlSelf->top__DOT__alu_result = 0xffffffffffffffffULL;
                    } else {
                        top__DOT__execute_alu__DOT__word_result 
                            = VL_DIV_III(32, (IData)(top__DOT__alu_a), (IData)(top__DOT__alu_b));
                        vlSelf->top__DOT__alu_result 
                            = (((QData)((IData)((- (IData)(
                                                           (top__DOT__execute_alu__DOT__word_result 
                                                            >> 0x1fU))))) 
                                << 0x20U) | (QData)((IData)(top__DOT__execute_alu__DOT__word_result)));
                    }
                } else if ((2U & (IData)(vlSelf->top__DOT__codeword))) {
                    if ((1U & (IData)(vlSelf->top__DOT__codeword))) {
                        if ((0U == (IData)(top__DOT__alu_b))) {
                            vlSelf->top__DOT__alu_result = 0xffffffffffffffffULL;
                        } else if (((0x80000000U == (IData)(top__DOT__alu_a)) 
                                    & (0xffffffffU 
                                       == (IData)(top__DOT__alu_b)))) {
                            vlSelf->top__DOT__alu_result 
                                = (((QData)((IData)(
                                                    (- (IData)(
                                                               (1U 
                                                                & (IData)(
                                                                          (top__DOT__alu_a 
                                                                           >> 0x1fU))))))) 
                                    << 0x20U) | (QData)((IData)(top__DOT__alu_a)));
                        } else {
                            top__DOT__execute_alu__DOT__word_result 
                                = VL_DIVS_III(32, (IData)(top__DOT__alu_a), (IData)(top__DOT__alu_b));
                            vlSelf->top__DOT__alu_result 
                                = (((QData)((IData)(
                                                    (- (IData)(
                                                               (top__DOT__execute_alu__DOT__word_result 
                                                                >> 0x1fU))))) 
                                    << 0x20U) | (QData)((IData)(top__DOT__execute_alu__DOT__word_result)));
                        }
                    } else {
                        top__DOT__execute_alu__DOT__word_result 
                            = ((IData)(top__DOT__alu_a) 
                               * (IData)(top__DOT__alu_b));
                        vlSelf->top__DOT__alu_result 
                            = (((QData)((IData)((- (IData)(
                                                           (top__DOT__execute_alu__DOT__word_result 
                                                            >> 0x1fU))))) 
                                << 0x20U) | (QData)((IData)(top__DOT__execute_alu__DOT__word_result)));
                    }
                } else if ((1U & (IData)(vlSelf->top__DOT__codeword))) {
                    top__DOT__execute_alu__DOT__word_result 
                        = VL_SHIFTRS_III(32,32,5, (IData)(top__DOT__alu_a), 
                                         (0x1fU & (IData)(top__DOT__alu_b)));
                    vlSelf->top__DOT__alu_result = 
                        (((QData)((IData)((- (IData)(
                                                     (top__DOT__execute_alu__DOT__word_result 
                                                      >> 0x1fU))))) 
                          << 0x20U) | (QData)((IData)(top__DOT__execute_alu__DOT__word_result)));
                } else {
                    top__DOT__execute_alu__DOT__word_result 
                        = ((IData)(top__DOT__alu_a) 
                           >> (0x1fU & (IData)(top__DOT__alu_b)));
                    vlSelf->top__DOT__alu_result = 
                        (((QData)((IData)((- (IData)(
                                                     (top__DOT__execute_alu__DOT__word_result 
                                                      >> 0x1fU))))) 
                          << 0x20U) | (QData)((IData)(top__DOT__execute_alu__DOT__word_result)));
                }
            } else if ((4U & (IData)(vlSelf->top__DOT__codeword))) {
                if ((2U & (IData)(vlSelf->top__DOT__codeword))) {
                    if ((1U & (IData)(vlSelf->top__DOT__codeword))) {
                        top__DOT__execute_alu__DOT__word_result 
                            = ((IData)(top__DOT__alu_a) 
                               << (0x1fU & (IData)(top__DOT__alu_b)));
                        vlSelf->top__DOT__alu_result 
                            = (((QData)((IData)((- (IData)(
                                                           (top__DOT__execute_alu__DOT__word_result 
                                                            >> 0x1fU))))) 
                                << 0x20U) | (QData)((IData)(top__DOT__execute_alu__DOT__word_result)));
                    } else {
                        top__DOT__execute_alu__DOT__word_result 
                            = ((IData)(top__DOT__alu_a) 
                               - (IData)(top__DOT__alu_b));
                        vlSelf->top__DOT__alu_result 
                            = (((QData)((IData)((- (IData)(
                                                           (top__DOT__execute_alu__DOT__word_result 
                                                            >> 0x1fU))))) 
                                << 0x20U) | (QData)((IData)(top__DOT__execute_alu__DOT__word_result)));
                    }
                } else if ((1U & (IData)(vlSelf->top__DOT__codeword))) {
                    top__DOT__execute_alu__DOT__word_result 
                        = ((IData)(top__DOT__alu_a) 
                           + (IData)(top__DOT__alu_b));
                    vlSelf->top__DOT__alu_result = 
                        (((QData)((IData)((- (IData)(
                                                     (top__DOT__execute_alu__DOT__word_result 
                                                      >> 0x1fU))))) 
                          << 0x20U) | (QData)((IData)(top__DOT__execute_alu__DOT__word_result)));
                } else {
                    top__DOT__execute_alu__DOT__word_result 
                        = VL_SHIFTRS_III(32,32,5, (IData)(top__DOT__alu_a), 
                                         (0x1fU & (IData)(top__DOT__alu_b)));
                    vlSelf->top__DOT__alu_result = 
                        (((QData)((IData)((- (IData)(
                                                     (top__DOT__execute_alu__DOT__word_result 
                                                      >> 0x1fU))))) 
                          << 0x20U) | (QData)((IData)(top__DOT__execute_alu__DOT__word_result)));
                }
            } else if ((2U & (IData)(vlSelf->top__DOT__codeword))) {
                if ((1U & (IData)(vlSelf->top__DOT__codeword))) {
                    top__DOT__execute_alu__DOT__word_result 
                        = ((IData)(top__DOT__alu_a) 
                           >> (0x1fU & (IData)(top__DOT__alu_b)));
                    vlSelf->top__DOT__alu_result = 
                        (((QData)((IData)((- (IData)(
                                                     (top__DOT__execute_alu__DOT__word_result 
                                                      >> 0x1fU))))) 
                          << 0x20U) | (QData)((IData)(top__DOT__execute_alu__DOT__word_result)));
                } else {
                    top__DOT__execute_alu__DOT__word_result 
                        = ((IData)(top__DOT__alu_a) 
                           << (0x1fU & (IData)(top__DOT__alu_b)));
                    vlSelf->top__DOT__alu_result = 
                        (((QData)((IData)((- (IData)(
                                                     (top__DOT__execute_alu__DOT__word_result 
                                                      >> 0x1fU))))) 
                          << 0x20U) | (QData)((IData)(top__DOT__execute_alu__DOT__word_result)));
                }
            } else if ((1U & (IData)(vlSelf->top__DOT__codeword))) {
                top__DOT__execute_alu__DOT__word_result 
                    = ((IData)(top__DOT__alu_a) + (IData)(top__DOT__alu_b));
                vlSelf->top__DOT__alu_result = (((QData)((IData)(
                                                                 (- (IData)(
                                                                            (top__DOT__execute_alu__DOT__word_result 
                                                                             >> 0x1fU))))) 
                                                 << 0x20U) 
                                                | (QData)((IData)(top__DOT__execute_alu__DOT__word_result)));
            } else {
                vlSelf->top__DOT__alu_result = ((0ULL 
                                                 == top__DOT__alu_b)
                                                 ? top__DOT__alu_a
                                                 : 
                                                VL_MODDIV_QQQ(64, top__DOT__alu_a, top__DOT__alu_b));
            }
        } else {
            vlSelf->top__DOT__alu_result = ((8U & (IData)(vlSelf->top__DOT__codeword))
                                             ? ((4U 
                                                 & (IData)(vlSelf->top__DOT__codeword))
                                                 ? 
                                                ((2U 
                                                  & (IData)(vlSelf->top__DOT__codeword))
                                                  ? 
                                                 ((1U 
                                                   & (IData)(vlSelf->top__DOT__codeword))
                                                   ? 
                                                  ((0ULL 
                                                    == top__DOT__alu_b)
                                                    ? top__DOT__alu_a
                                                    : 
                                                   (((0x8000000000000000ULL 
                                                      == top__DOT__alu_a) 
                                                     & (0xffffffffffffffffULL 
                                                        == top__DOT__alu_b))
                                                     ? 0ULL
                                                     : 
                                                    VL_MODDIVS_QQQ(64, top__DOT__alu_a, top__DOT__alu_b)))
                                                   : 
                                                  ((0ULL 
                                                    == top__DOT__alu_b)
                                                    ? 0xffffffffffffffffULL
                                                    : 
                                                   VL_DIV_QQQ(64, top__DOT__alu_a, top__DOT__alu_b)))
                                                  : 
                                                 ((1U 
                                                   & (IData)(vlSelf->top__DOT__codeword))
                                                   ? 
                                                  ((0ULL 
                                                    == top__DOT__alu_b)
                                                    ? 0xffffffffffffffffULL
                                                    : 
                                                   (((0x8000000000000000ULL 
                                                      == top__DOT__alu_a) 
                                                     & (0xffffffffffffffffULL 
                                                        == top__DOT__alu_b))
                                                     ? top__DOT__alu_a
                                                     : 
                                                    VL_DIVS_QQQ(64, top__DOT__alu_a, top__DOT__alu_b)))
                                                   : 
                                                  (((QData)((IData)(
                                                                    top__DOT__execute_alu__DOT__unsigned_product[3U])) 
                                                    << 0x20U) 
                                                   | (QData)((IData)(
                                                                     top__DOT__execute_alu__DOT__unsigned_product[2U])))))
                                                 : 
                                                ((2U 
                                                  & (IData)(vlSelf->top__DOT__codeword))
                                                  ? 
                                                 ((1U 
                                                   & (IData)(vlSelf->top__DOT__codeword))
                                                   ? 
                                                  (((QData)((IData)(
                                                                    top__DOT__execute_alu__DOT__signed_unsigned_product[3U])) 
                                                    << 0x20U) 
                                                   | (QData)((IData)(
                                                                     top__DOT__execute_alu__DOT__signed_unsigned_product[2U])))
                                                   : 
                                                  (((QData)((IData)(
                                                                    top__DOT__execute_alu__DOT__signed_product[3U])) 
                                                    << 0x20U) 
                                                   | (QData)((IData)(
                                                                     top__DOT__execute_alu__DOT__signed_product[2U]))))
                                                  : 
                                                 ((1U 
                                                   & (IData)(vlSelf->top__DOT__codeword))
                                                   ? 
                                                  (top__DOT__alu_a 
                                                   * top__DOT__alu_b)
                                                   : 
                                                  (top__DOT__alu_a 
                                                   & top__DOT__alu_b))))
                                             : ((4U 
                                                 & (IData)(vlSelf->top__DOT__codeword))
                                                 ? 
                                                ((2U 
                                                  & (IData)(vlSelf->top__DOT__codeword))
                                                  ? 
                                                 ((1U 
                                                   & (IData)(vlSelf->top__DOT__codeword))
                                                   ? 
                                                  (top__DOT__alu_a 
                                                   | top__DOT__alu_b)
                                                   : 
                                                  VL_SHIFTRS_QQI(64,64,6, top__DOT__alu_a, 
                                                                 (0x3fU 
                                                                  & (IData)(top__DOT__alu_b))))
                                                  : 
                                                 ((1U 
                                                   & (IData)(vlSelf->top__DOT__codeword))
                                                   ? 
                                                  (top__DOT__alu_a 
                                                   >> 
                                                   (0x3fU 
                                                    & (IData)(top__DOT__alu_b)))
                                                   : 
                                                  (top__DOT__alu_a 
                                                   ^ top__DOT__alu_b)))
                                                 : 
                                                ((2U 
                                                  & (IData)(vlSelf->top__DOT__codeword))
                                                  ? 
                                                 ((1U 
                                                   & (IData)(vlSelf->top__DOT__codeword))
                                                   ? 
                                                  ((top__DOT__alu_a 
                                                    < top__DOT__alu_b)
                                                    ? 1ULL
                                                    : 0ULL)
                                                   : 
                                                  (VL_LTS_IQQ(64, top__DOT__alu_a, top__DOT__alu_b)
                                                    ? 1ULL
                                                    : 0ULL))
                                                  : 
                                                 ((1U 
                                                   & (IData)(vlSelf->top__DOT__codeword))
                                                   ? 
                                                  (top__DOT__alu_a 
                                                   << 
                                                   (0x3fU 
                                                    & (IData)(top__DOT__alu_b)))
                                                   : 
                                                  (top__DOT__alu_a 
                                                   - top__DOT__alu_b)))));
        }
    } else {
        vlSelf->top__DOT__alu_result = ((0x10U & (IData)(vlSelf->top__DOT__codeword))
                                         ? ((8U & (IData)(vlSelf->top__DOT__codeword))
                                             ? ((4U 
                                                 & (IData)(vlSelf->top__DOT__codeword))
                                                 ? 
                                                ((2U 
                                                  & (IData)(vlSelf->top__DOT__codeword))
                                                  ? 
                                                 ((1U 
                                                   & (IData)(vlSelf->top__DOT__codeword))
                                                   ? 
                                                  (top__DOT__alu_a 
                                                   + top__DOT__alu_b)
                                                   : 
                                                  VL_SHIFTRS_QQI(64,64,6, top__DOT__alu_a, 
                                                                 (0x3fU 
                                                                  & (IData)(top__DOT__alu_b))))
                                                  : 
                                                 ((1U 
                                                   & (IData)(vlSelf->top__DOT__codeword))
                                                   ? 
                                                  (top__DOT__alu_a 
                                                   >> 
                                                   (0x3fU 
                                                    & (IData)(top__DOT__alu_b)))
                                                   : 
                                                  (top__DOT__alu_a 
                                                   << 
                                                   (0x3fU 
                                                    & (IData)(top__DOT__alu_b)))))
                                                 : 
                                                ((2U 
                                                  & (IData)(vlSelf->top__DOT__codeword))
                                                  ? 
                                                 ((1U 
                                                   & (IData)(vlSelf->top__DOT__codeword))
                                                   ? 
                                                  (top__DOT__alu_a 
                                                   & top__DOT__alu_b)
                                                   : 
                                                  (top__DOT__alu_a 
                                                   | top__DOT__alu_b))
                                                  : 
                                                 ((1U 
                                                   & (IData)(vlSelf->top__DOT__codeword))
                                                   ? 
                                                  (top__DOT__alu_a 
                                                   ^ top__DOT__alu_b)
                                                   : 
                                                  ((top__DOT__alu_a 
                                                    < top__DOT__alu_b)
                                                    ? 1ULL
                                                    : 0ULL))))
                                             : ((4U 
                                                 & (IData)(vlSelf->top__DOT__codeword))
                                                 ? 
                                                ((2U 
                                                  & (IData)(vlSelf->top__DOT__codeword))
                                                  ? 
                                                 ((1U 
                                                   & (IData)(vlSelf->top__DOT__codeword))
                                                   ? 
                                                  (VL_LTS_IQQ(64, top__DOT__alu_a, top__DOT__alu_b)
                                                    ? 1ULL
                                                    : 0ULL)
                                                   : 
                                                  (top__DOT__alu_a 
                                                   + top__DOT__alu_b))
                                                  : 0ULL)
                                                 : 0ULL))
                                         : ((8U & (IData)(vlSelf->top__DOT__codeword))
                                             ? 0ULL
                                             : ((4U 
                                                 & (IData)(vlSelf->top__DOT__codeword))
                                                 ? 0ULL
                                                 : 
                                                ((2U 
                                                  & (IData)(vlSelf->top__DOT__codeword))
                                                  ? 
                                                 ((1U 
                                                   & (IData)(vlSelf->top__DOT__codeword))
                                                   ? 0ULL
                                                   : 
                                                  (top__DOT__alu_a 
                                                   + top__DOT__alu_b))
                                                  : 
                                                 ((1U 
                                                   & (IData)(vlSelf->top__DOT__codeword))
                                                   ? top__DOT__alu_b
                                                   : 0ULL)))));
    }
}
