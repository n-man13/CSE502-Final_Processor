// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop__pch.h"
#include "Vtop___024root.h"

VL_ATTR_COLD void Vtop___024root___eval_static(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_static\n"); );
}

VL_ATTR_COLD void Vtop___024root___eval_initial__TOP(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_initial(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_initial\n"); );
    // Body
    Vtop___024root___eval_initial__TOP(vlSelf);
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = vlSelf->clk;
}

VL_ATTR_COLD void Vtop___024root___eval_initial__TOP(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_initial__TOP\n"); );
    // Body
    VL_WRITEF("Initializing top, entry point = 0x%x\n",
              64,vlSelf->entry);
    vlSelf->m_axi_awid = 0U;
    vlSelf->m_axi_awaddr = 0ULL;
    vlSelf->m_axi_awlen = 0U;
    vlSelf->m_axi_awsize = 0U;
    vlSelf->m_axi_awburst = 0U;
    vlSelf->m_axi_awlock = 0U;
    vlSelf->m_axi_awcache = 0U;
    vlSelf->m_axi_awprot = 0U;
    vlSelf->m_axi_wvalid = 0U;
    vlSelf->m_axi_wdata = 0ULL;
    vlSelf->m_axi_wstrb = 0U;
    vlSelf->m_axi_wlast = 0U;
    vlSelf->m_axi_bready = 0U;
    vlSelf->m_axi_acready = 0U;
    vlSelf->m_axi_arlen = 7U;
    vlSelf->m_axi_arsize = 3U;
    vlSelf->m_axi_arburst = 2U;
    vlSelf->m_axi_arid = 0U;
    vlSelf->m_axi_arlock = 0U;
    vlSelf->m_axi_arcache = 0U;
    vlSelf->m_axi_arprot = 0U;
}

VL_ATTR_COLD void Vtop___024root___eval_final(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_final\n"); );
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__stl(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vtop___024root___eval_phase__stl(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_settle(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_settle\n"); );
    // Init
    IData/*31:0*/ __VstlIterCount;
    CData/*0:0*/ __VstlContinue;
    // Body
    __VstlIterCount = 0U;
    vlSelf->__VstlFirstIteration = 1U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        if (VL_UNLIKELY((0x64U < __VstlIterCount))) {
#ifdef VL_DEBUG
            Vtop___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("top.sv", 697, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (Vtop___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelf->__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__stl(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__stl\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VstlTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VstlTriggered.word(0U))) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtop___024root___stl_sequent__TOP__0(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___stl_sequent__TOP__0\n"); );
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
    VlWide<4>/*127:0*/ __Vtemp_1;
    VlWide<4>/*127:0*/ __Vtemp_2;
    VlWide<4>/*127:0*/ __Vtemp_3;
    VlWide<4>/*127:0*/ __Vtemp_4;
    VlWide<4>/*127:0*/ __Vtemp_5;
    VlWide<4>/*127:0*/ __Vtemp_6;
    // Body
    vlSelf->m_axi_araddr = (0xffffffffffffffc0ULL & vlSelf->top__DOT__pc);
    vlSelf->top__DOT__next_pc = (4ULL + vlSelf->top__DOT__pc);
    vlSelf->m_axi_arvalid = (1U == (IData)(vlSelf->top__DOT__state));
    vlSelf->m_axi_rready = (2U == (IData)(vlSelf->top__DOT__state));
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
    __Vtemp_1[0U] = (IData)(top__DOT__alu_a);
    __Vtemp_1[1U] = (IData)((top__DOT__alu_a >> 0x20U));
    __Vtemp_1[2U] = (IData)((- (QData)((IData)((1U 
                                                & (IData)(
                                                          (top__DOT__alu_a 
                                                           >> 0x3fU)))))));
    __Vtemp_1[3U] = (IData)(((- (QData)((IData)((1U 
                                                 & (IData)(
                                                           (top__DOT__alu_a 
                                                            >> 0x3fU)))))) 
                             >> 0x20U));
    __Vtemp_2[0U] = (IData)(top__DOT__alu_b);
    __Vtemp_2[1U] = (IData)((top__DOT__alu_b >> 0x20U));
    __Vtemp_2[2U] = (IData)((- (QData)((IData)((1U 
                                                & (IData)(
                                                          (top__DOT__alu_b 
                                                           >> 0x3fU)))))));
    __Vtemp_2[3U] = (IData)(((- (QData)((IData)((1U 
                                                 & (IData)(
                                                           (top__DOT__alu_b 
                                                            >> 0x3fU)))))) 
                             >> 0x20U));
    VL_MULS_WWW(128, top__DOT__execute_alu__DOT__signed_product, __Vtemp_1, __Vtemp_2);
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
    __Vtemp_4[2U] = 0U;
    __Vtemp_4[3U] = 0U;
    VL_MULS_WWW(128, top__DOT__execute_alu__DOT__signed_unsigned_product, __Vtemp_3, __Vtemp_4);
    __Vtemp_5[0U] = (IData)(top__DOT__alu_a);
    __Vtemp_5[1U] = (IData)((top__DOT__alu_a >> 0x20U));
    __Vtemp_5[2U] = 0U;
    __Vtemp_5[3U] = 0U;
    __Vtemp_6[0U] = (IData)(top__DOT__alu_b);
    __Vtemp_6[1U] = (IData)((top__DOT__alu_b >> 0x20U));
    __Vtemp_6[2U] = 0U;
    __Vtemp_6[3U] = 0U;
    VL_MUL_W(4, top__DOT__execute_alu__DOT__unsigned_product, __Vtemp_5, __Vtemp_6);
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

VL_ATTR_COLD void Vtop___024root___eval_stl(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_stl\n"); );
    // Body
    if ((1ULL & vlSelf->__VstlTriggered.word(0U))) {
        Vtop___024root___stl_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD void Vtop___024root___eval_triggers__stl(Vtop___024root* vlSelf);

VL_ATTR_COLD bool Vtop___024root___eval_phase__stl(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__stl\n"); );
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    Vtop___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelf->__VstlTriggered.any();
    if (__VstlExecute) {
        Vtop___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__act\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VactTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__nba(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__nba\n"); );
    // Body
    if ((1U & (~ (IData)(vlSelf->__VnbaTriggered.any())))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelf->__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vtop___024root___ctor_var_reset(Vtop___024root* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___ctor_var_reset\n"); );
    // Body
    vlSelf->clk = VL_RAND_RESET_I(1);
    vlSelf->reset = VL_RAND_RESET_I(1);
    vlSelf->hz32768timer = VL_RAND_RESET_I(1);
    vlSelf->entry = VL_RAND_RESET_Q(64);
    vlSelf->stackptr = VL_RAND_RESET_Q(64);
    vlSelf->satp = VL_RAND_RESET_Q(64);
    vlSelf->m_axi_awid = VL_RAND_RESET_I(13);
    vlSelf->m_axi_awaddr = VL_RAND_RESET_Q(64);
    vlSelf->m_axi_awlen = VL_RAND_RESET_I(8);
    vlSelf->m_axi_awsize = VL_RAND_RESET_I(3);
    vlSelf->m_axi_awburst = VL_RAND_RESET_I(2);
    vlSelf->m_axi_awlock = VL_RAND_RESET_I(1);
    vlSelf->m_axi_awcache = VL_RAND_RESET_I(4);
    vlSelf->m_axi_awprot = VL_RAND_RESET_I(3);
    vlSelf->m_axi_awvalid = VL_RAND_RESET_I(1);
    vlSelf->m_axi_awready = VL_RAND_RESET_I(1);
    vlSelf->m_axi_wdata = VL_RAND_RESET_Q(64);
    vlSelf->m_axi_wstrb = VL_RAND_RESET_I(8);
    vlSelf->m_axi_wlast = VL_RAND_RESET_I(1);
    vlSelf->m_axi_wvalid = VL_RAND_RESET_I(1);
    vlSelf->m_axi_wready = VL_RAND_RESET_I(1);
    vlSelf->m_axi_bid = VL_RAND_RESET_I(13);
    vlSelf->m_axi_bresp = VL_RAND_RESET_I(2);
    vlSelf->m_axi_bvalid = VL_RAND_RESET_I(1);
    vlSelf->m_axi_bready = VL_RAND_RESET_I(1);
    vlSelf->m_axi_arid = VL_RAND_RESET_I(13);
    vlSelf->m_axi_araddr = VL_RAND_RESET_Q(64);
    vlSelf->m_axi_arlen = VL_RAND_RESET_I(8);
    vlSelf->m_axi_arsize = VL_RAND_RESET_I(3);
    vlSelf->m_axi_arburst = VL_RAND_RESET_I(2);
    vlSelf->m_axi_arlock = VL_RAND_RESET_I(1);
    vlSelf->m_axi_arcache = VL_RAND_RESET_I(4);
    vlSelf->m_axi_arprot = VL_RAND_RESET_I(3);
    vlSelf->m_axi_arvalid = VL_RAND_RESET_I(1);
    vlSelf->m_axi_arready = VL_RAND_RESET_I(1);
    vlSelf->m_axi_rid = VL_RAND_RESET_I(13);
    vlSelf->m_axi_rdata = VL_RAND_RESET_Q(64);
    vlSelf->m_axi_rresp = VL_RAND_RESET_I(2);
    vlSelf->m_axi_rlast = VL_RAND_RESET_I(1);
    vlSelf->m_axi_rvalid = VL_RAND_RESET_I(1);
    vlSelf->m_axi_rready = VL_RAND_RESET_I(1);
    vlSelf->m_axi_acvalid = VL_RAND_RESET_I(1);
    vlSelf->m_axi_acready = VL_RAND_RESET_I(1);
    vlSelf->m_axi_acaddr = VL_RAND_RESET_Q(64);
    vlSelf->m_axi_acsnoop = VL_RAND_RESET_I(4);
    vlSelf->top__DOT__pc = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__next_pc = VL_RAND_RESET_Q(64);
    VL_RAND_RESET_W(512, vlSelf->top__DOT__fetched_line);
    vlSelf->top__DOT__beat_count = VL_RAND_RESET_I(3);
    vlSelf->top__DOT__instr = VL_RAND_RESET_I(32);
    vlSelf->top__DOT__alu_result = VL_RAND_RESET_Q(64);
    vlSelf->top__DOT__state = VL_RAND_RESET_I(2);
    vlSelf->top__DOT__codeword = VL_RAND_RESET_I(7);
    vlSelf->top__DOT__has_rd = VL_RAND_RESET_I(1);
    for (int __Vi0 = 0; __Vi0 < 32; ++__Vi0) {
        vlSelf->top__DOT__registers__DOT__regs[__Vi0] = VL_RAND_RESET_Q(64);
    }
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = VL_RAND_RESET_I(1);
}
