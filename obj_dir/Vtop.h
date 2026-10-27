// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Primary model header
//
// This header should be included by all source files instantiating the design.
// The class here is then constructed to instantiate the design.
// See the Verilator manual for examples.

#ifndef VERILATED_VTOP_H_
#define VERILATED_VTOP_H_  // guard

#include "verilated.h"
#include "svdpi.h"

class Vtop__Syms;
class Vtop___024root;
class Vtop___024unit;


// This class is the main interface to the Verilated model
class alignas(VL_CACHE_LINE_BYTES) Vtop VL_NOT_FINAL : public VerilatedModel {
  private:
    // Symbol table holding complete model state (owned by this class)
    Vtop__Syms* const vlSymsp;

  public:

    // PORTS
    // The application code writes and reads these signals to
    // propagate new values into/out from the Verilated model.
    VL_IN8(&clk,0,0);
    VL_IN8(&reset,0,0);
    VL_IN8(&hz32768timer,0,0);
    VL_OUT8(&m_axi_awlen,7,0);
    VL_OUT8(&m_axi_awsize,2,0);
    VL_OUT8(&m_axi_awburst,1,0);
    VL_OUT8(&m_axi_awlock,0,0);
    VL_OUT8(&m_axi_awcache,3,0);
    VL_OUT8(&m_axi_awprot,2,0);
    VL_OUT8(&m_axi_awvalid,0,0);
    VL_IN8(&m_axi_awready,0,0);
    VL_OUT8(&m_axi_wstrb,7,0);
    VL_OUT8(&m_axi_wlast,0,0);
    VL_OUT8(&m_axi_wvalid,0,0);
    VL_IN8(&m_axi_wready,0,0);
    VL_IN8(&m_axi_bresp,1,0);
    VL_IN8(&m_axi_bvalid,0,0);
    VL_OUT8(&m_axi_bready,0,0);
    VL_OUT8(&m_axi_arlen,7,0);
    VL_OUT8(&m_axi_arsize,2,0);
    VL_OUT8(&m_axi_arburst,1,0);
    VL_OUT8(&m_axi_arlock,0,0);
    VL_OUT8(&m_axi_arcache,3,0);
    VL_OUT8(&m_axi_arprot,2,0);
    VL_OUT8(&m_axi_arvalid,0,0);
    VL_IN8(&m_axi_arready,0,0);
    VL_IN8(&m_axi_rresp,1,0);
    VL_IN8(&m_axi_rlast,0,0);
    VL_IN8(&m_axi_rvalid,0,0);
    VL_OUT8(&m_axi_rready,0,0);
    VL_IN8(&m_axi_acvalid,0,0);
    VL_OUT8(&m_axi_acready,0,0);
    VL_IN8(&m_axi_acsnoop,3,0);
    VL_OUT16(&m_axi_awid,12,0);
    VL_IN16(&m_axi_bid,12,0);
    VL_OUT16(&m_axi_arid,12,0);
    VL_IN16(&m_axi_rid,12,0);
    VL_IN64(&entry,63,0);
    VL_IN64(&stackptr,63,0);
    VL_IN64(&satp,63,0);
    VL_OUT64(&m_axi_awaddr,63,0);
    VL_OUT64(&m_axi_wdata,63,0);
    VL_OUT64(&m_axi_araddr,63,0);
    VL_IN64(&m_axi_rdata,63,0);
    VL_IN64(&m_axi_acaddr,63,0);

    // CELLS
    // Public to allow access to /* verilator public */ items.
    // Otherwise the application code can consider these internals.
    Vtop___024unit* const __PVT____024unit;

    // Root instance pointer to allow access to model internals,
    // including inlined /* verilator public_flat_* */ items.
    Vtop___024root* const rootp;

    // CONSTRUCTORS
    /// Construct the model; called by application code
    /// If contextp is null, then the model will use the default global context
    /// If name is "", then makes a wrapper with a
    /// single model invisible with respect to DPI scope names.
    explicit Vtop(VerilatedContext* contextp, const char* name = "TOP");
    explicit Vtop(const char* name = "TOP");
    /// Destroy the model; called (often implicitly) by application code
    virtual ~Vtop();
  private:
    VL_UNCOPYABLE(Vtop);  ///< Copying not allowed

  public:
    // API METHODS
    /// Evaluate the model.  Application must call when inputs change.
    void eval() { eval_step(); }
    /// Evaluate when calling multiple units/models per time step.
    void eval_step();
    /// Evaluate at end of a timestep for tracing, when using eval_step().
    /// Application must call after all eval() and before time changes.
    void eval_end_step() {}
    /// Simulation complete, run final blocks.  Application must call on completion.
    void final();
    /// Are there scheduled events to handle?
    bool eventsPending();
    /// Returns time at next time slot. Aborts if !eventsPending()
    uint64_t nextTimeSlot();
    /// Trace signals in the model; called by application code
    void trace(VerilatedVcdC* tfp, int levels, int options = 0);
    /// Retrieve name of this model instance (as passed to constructor).
    const char* name() const;

    // Abstract methods from VerilatedModel
    const char* hierName() const override final;
    const char* modelName() const override final;
    unsigned threads() const override final;
    /// Prepare for cloning the model at the process level (e.g. fork in Linux)
    /// Release necessary resources. Called before cloning.
    void prepareClone() const;
    /// Re-init after cloning the model at the process level (e.g. fork in Linux)
    /// Re-allocate necessary resources. Called after cloning.
    void atClone() const;
};

#endif  // guard
