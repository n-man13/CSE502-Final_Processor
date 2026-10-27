// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop__pch.h"
#include "Vtop___024unit.h"

VL_ATTR_COLD void Vtop___024unit___ctor_var_reset(Vtop___024unit* vlSelf) {
    if (false && vlSelf) {}  // Prevent unused
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vtop___024unit___ctor_var_reset\n"); );
    // Body
    vlSelf->__Venumtab_enum_name0.atDefault() = std::string{""};
    vlSelf->__Venumtab_enum_name0.at(0) = std::string{"UNKNOWN"};
    vlSelf->__Venumtab_enum_name0.at(1) = std::string{"LUI"};
    vlSelf->__Venumtab_enum_name0.at(2) = std::string{"AUIPC"};
    vlSelf->__Venumtab_enum_name0.at(3) = std::string{"JAL"};
    vlSelf->__Venumtab_enum_name0.at(4) = std::string{"JALR"};
    vlSelf->__Venumtab_enum_name0.at(5) = std::string{"BEQ"};
    vlSelf->__Venumtab_enum_name0.at(6) = std::string{"BNE"};
    vlSelf->__Venumtab_enum_name0.at(7) = std::string{"BLT"};
    vlSelf->__Venumtab_enum_name0.at(8) = std::string{"BGE"};
    vlSelf->__Venumtab_enum_name0.at(9) = std::string{"BLTU"};
    vlSelf->__Venumtab_enum_name0.at(10) = std::string{"BGEU"};
    vlSelf->__Venumtab_enum_name0.at(11) = std::string{"LB"};
    vlSelf->__Venumtab_enum_name0.at(12) = std::string{"LH"};
    vlSelf->__Venumtab_enum_name0.at(13) = std::string{"LW"};
    vlSelf->__Venumtab_enum_name0.at(14) = std::string{"LBU"};
    vlSelf->__Venumtab_enum_name0.at(15) = std::string{"LHU"};
    vlSelf->__Venumtab_enum_name0.at(16) = std::string{"LWU"};
    vlSelf->__Venumtab_enum_name0.at(17) = std::string{"LD"};
    vlSelf->__Venumtab_enum_name0.at(18) = std::string{"SB"};
    vlSelf->__Venumtab_enum_name0.at(19) = std::string{"SH"};
    vlSelf->__Venumtab_enum_name0.at(20) = std::string{"SW"};
    vlSelf->__Venumtab_enum_name0.at(21) = std::string{"SD"};
    vlSelf->__Venumtab_enum_name0.at(22) = std::string{"ADDI"};
    vlSelf->__Venumtab_enum_name0.at(23) = std::string{"SLTI"};
    vlSelf->__Venumtab_enum_name0.at(24) = std::string{"SLTIU"};
    vlSelf->__Venumtab_enum_name0.at(25) = std::string{"XORI"};
    vlSelf->__Venumtab_enum_name0.at(26) = std::string{"ORI"};
    vlSelf->__Venumtab_enum_name0.at(27) = std::string{"ANDI"};
    vlSelf->__Venumtab_enum_name0.at(28) = std::string{"SLLI"};
    vlSelf->__Venumtab_enum_name0.at(29) = std::string{"SRLI"};
    vlSelf->__Venumtab_enum_name0.at(30) = std::string{"SRAI"};
    vlSelf->__Venumtab_enum_name0.at(31) = std::string{"ADD"};
    vlSelf->__Venumtab_enum_name0.at(32) = std::string{"SUB"};
    vlSelf->__Venumtab_enum_name0.at(33) = std::string{"SLL"};
    vlSelf->__Venumtab_enum_name0.at(34) = std::string{"SLT"};
    vlSelf->__Venumtab_enum_name0.at(35) = std::string{"SLTU"};
    vlSelf->__Venumtab_enum_name0.at(36) = std::string{"XOR"};
    vlSelf->__Venumtab_enum_name0.at(37) = std::string{"SRL"};
    vlSelf->__Venumtab_enum_name0.at(38) = std::string{"SRA"};
    vlSelf->__Venumtab_enum_name0.at(39) = std::string{"OR"};
    vlSelf->__Venumtab_enum_name0.at(40) = std::string{"AND"};
    vlSelf->__Venumtab_enum_name0.at(41) = std::string{"MUL"};
    vlSelf->__Venumtab_enum_name0.at(42) = std::string{"MULH"};
    vlSelf->__Venumtab_enum_name0.at(43) = std::string{"MULHSU"};
    vlSelf->__Venumtab_enum_name0.at(44) = std::string{"MULHU"};
    vlSelf->__Venumtab_enum_name0.at(45) = std::string{"DIV"};
    vlSelf->__Venumtab_enum_name0.at(46) = std::string{"DIVU"};
    vlSelf->__Venumtab_enum_name0.at(47) = std::string{"REM"};
    vlSelf->__Venumtab_enum_name0.at(48) = std::string{"REMU"};
    vlSelf->__Venumtab_enum_name0.at(49) = std::string{"ADDIW"};
    vlSelf->__Venumtab_enum_name0.at(50) = std::string{"SLLIW"};
    vlSelf->__Venumtab_enum_name0.at(51) = std::string{"SRLIW"};
    vlSelf->__Venumtab_enum_name0.at(52) = std::string{"SRAIW"};
    vlSelf->__Venumtab_enum_name0.at(53) = std::string{"ADDW"};
    vlSelf->__Venumtab_enum_name0.at(54) = std::string{"SUBW"};
    vlSelf->__Venumtab_enum_name0.at(55) = std::string{"SLLW"};
    vlSelf->__Venumtab_enum_name0.at(56) = std::string{"SRLW"};
    vlSelf->__Venumtab_enum_name0.at(57) = std::string{"SRAW"};
    vlSelf->__Venumtab_enum_name0.at(58) = std::string{"MULW"};
    vlSelf->__Venumtab_enum_name0.at(59) = std::string{"DIVW"};
    vlSelf->__Venumtab_enum_name0.at(60) = std::string{"DIVUW"};
    vlSelf->__Venumtab_enum_name0.at(61) = std::string{"REMW"};
    vlSelf->__Venumtab_enum_name0.at(62) = std::string{"REMUW"};
    vlSelf->__Venumtab_enum_name0.at(63) = std::string{"FENCE"};
    vlSelf->__Venumtab_enum_name0.at(64) = std::string{"FENCE_I"};
    vlSelf->__Venumtab_enum_name0.at(65) = std::string{"ECALL"};
    vlSelf->__Venumtab_enum_name0.at(66) = std::string{"EBREAK"};
    vlSelf->__Venumtab_enum_name0.at(67) = std::string{"CSRRW"};
    vlSelf->__Venumtab_enum_name0.at(68) = std::string{"CSRRS"};
    vlSelf->__Venumtab_enum_name0.at(69) = std::string{"CSRRC"};
    vlSelf->__Venumtab_enum_name0.at(70) = std::string{"CSRRWI"};
    vlSelf->__Venumtab_enum_name0.at(71) = std::string{"CSRRSI"};
    vlSelf->__Venumtab_enum_name0.at(72) = std::string{"CSRRCI"};
}
