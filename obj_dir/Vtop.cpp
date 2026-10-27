// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vtop__pch.h"

//============================================================
// Constructors

Vtop::Vtop(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vtop__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , reset{vlSymsp->TOP.reset}
    , hz32768timer{vlSymsp->TOP.hz32768timer}
    , m_axi_awlen{vlSymsp->TOP.m_axi_awlen}
    , m_axi_awsize{vlSymsp->TOP.m_axi_awsize}
    , m_axi_awburst{vlSymsp->TOP.m_axi_awburst}
    , m_axi_awlock{vlSymsp->TOP.m_axi_awlock}
    , m_axi_awcache{vlSymsp->TOP.m_axi_awcache}
    , m_axi_awprot{vlSymsp->TOP.m_axi_awprot}
    , m_axi_awvalid{vlSymsp->TOP.m_axi_awvalid}
    , m_axi_awready{vlSymsp->TOP.m_axi_awready}
    , m_axi_wstrb{vlSymsp->TOP.m_axi_wstrb}
    , m_axi_wlast{vlSymsp->TOP.m_axi_wlast}
    , m_axi_wvalid{vlSymsp->TOP.m_axi_wvalid}
    , m_axi_wready{vlSymsp->TOP.m_axi_wready}
    , m_axi_bresp{vlSymsp->TOP.m_axi_bresp}
    , m_axi_bvalid{vlSymsp->TOP.m_axi_bvalid}
    , m_axi_bready{vlSymsp->TOP.m_axi_bready}
    , m_axi_arlen{vlSymsp->TOP.m_axi_arlen}
    , m_axi_arsize{vlSymsp->TOP.m_axi_arsize}
    , m_axi_arburst{vlSymsp->TOP.m_axi_arburst}
    , m_axi_arlock{vlSymsp->TOP.m_axi_arlock}
    , m_axi_arcache{vlSymsp->TOP.m_axi_arcache}
    , m_axi_arprot{vlSymsp->TOP.m_axi_arprot}
    , m_axi_arvalid{vlSymsp->TOP.m_axi_arvalid}
    , m_axi_arready{vlSymsp->TOP.m_axi_arready}
    , m_axi_rresp{vlSymsp->TOP.m_axi_rresp}
    , m_axi_rlast{vlSymsp->TOP.m_axi_rlast}
    , m_axi_rvalid{vlSymsp->TOP.m_axi_rvalid}
    , m_axi_rready{vlSymsp->TOP.m_axi_rready}
    , m_axi_acvalid{vlSymsp->TOP.m_axi_acvalid}
    , m_axi_acready{vlSymsp->TOP.m_axi_acready}
    , m_axi_acsnoop{vlSymsp->TOP.m_axi_acsnoop}
    , m_axi_awid{vlSymsp->TOP.m_axi_awid}
    , m_axi_bid{vlSymsp->TOP.m_axi_bid}
    , m_axi_arid{vlSymsp->TOP.m_axi_arid}
    , m_axi_rid{vlSymsp->TOP.m_axi_rid}
    , entry{vlSymsp->TOP.entry}
    , stackptr{vlSymsp->TOP.stackptr}
    , satp{vlSymsp->TOP.satp}
    , m_axi_awaddr{vlSymsp->TOP.m_axi_awaddr}
    , m_axi_wdata{vlSymsp->TOP.m_axi_wdata}
    , m_axi_araddr{vlSymsp->TOP.m_axi_araddr}
    , m_axi_rdata{vlSymsp->TOP.m_axi_rdata}
    , m_axi_acaddr{vlSymsp->TOP.m_axi_acaddr}
    , __PVT____024unit{vlSymsp->TOP.__PVT____024unit}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vtop::Vtop(const char* _vcname__)
    : Vtop(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vtop::~Vtop() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vtop___024root___eval_debug_assertions(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
void Vtop___024root___eval_static(Vtop___024root* vlSelf);
void Vtop___024root___eval_initial(Vtop___024root* vlSelf);
void Vtop___024root___eval_settle(Vtop___024root* vlSelf);
void Vtop___024root___eval(Vtop___024root* vlSelf);

void Vtop::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vtop::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vtop___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vtop___024root___eval_static(&(vlSymsp->TOP));
        Vtop___024root___eval_initial(&(vlSymsp->TOP));
        Vtop___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vtop___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vtop::eventsPending() { return false; }

uint64_t Vtop::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "%Error: No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vtop::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vtop___024root___eval_final(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop::final() {
    Vtop___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vtop::hierName() const { return vlSymsp->name(); }
const char* Vtop::modelName() const { return "Vtop"; }
unsigned Vtop::threads() const { return 1; }
void Vtop::prepareClone() const { contextp()->prepareClone(); }
void Vtop::atClone() const {
    contextp()->threadPoolpOnClone();
}

//============================================================
// Trace configuration

VL_ATTR_COLD void Vtop::trace(VerilatedVcdC* tfp, int levels, int options) {
    vl_fatal(__FILE__, __LINE__, __FILE__,"'Vtop::trace()' called on model that was Verilated without --trace option");
}
