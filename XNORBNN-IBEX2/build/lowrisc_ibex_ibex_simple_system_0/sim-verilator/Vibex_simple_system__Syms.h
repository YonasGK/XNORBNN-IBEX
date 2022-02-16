// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef _VIBEX_SIMPLE_SYSTEM__SYMS_H_
#define _VIBEX_SIMPLE_SYSTEM__SYMS_H_  // guard

#include "verilated_heavy.h"

// INCLUDE MODULE CLASSES
#include "Vibex_simple_system.h"

// DPI TYPES for DPI Export callbacks (Internal use)
typedef void (*Vibex_simple_system__Vcb_mhpmcounter_get_t) (Vibex_simple_system__Syms* __restrict vlSymsp, const IData/*31:0*/ index, QData/*63:0*/(&  mhpmcounter_get__Vfuncrtn));
typedef void (*Vibex_simple_system__Vcb_simutil_verilator_get_mem_t) (Vibex_simple_system__Syms* __restrict vlSymsp, const IData/*31:0*/ index, WData/*255:0*/(&  val)[8], IData/*31:0*/(&  simutil_verilator_get_mem__Vfuncrtn));
typedef void (*Vibex_simple_system__Vcb_simutil_verilator_memload_t) (Vibex_simple_system__Syms* __restrict vlSymsp, const std::string(&  file));
typedef void (*Vibex_simple_system__Vcb_simutil_verilator_set_mem_t) (Vibex_simple_system__Syms* __restrict vlSymsp, const IData/*31:0*/ index, const WData/*255:0*/ val[8], IData/*31:0*/(&  simutil_verilator_set_mem__Vfuncrtn));

// SYMS CLASS
class Vibex_simple_system__Syms : public VerilatedSyms {
  public:
    
    // LOCAL STATE
    const char* __Vm_namep;
    bool __Vm_activity;  ///< Used by trace routines to determine change occurred
    bool __Vm_didInit;
    
    // SUBCELL STATE
    Vibex_simple_system*           TOPp;
    
    // SCOPE NAMES
    VerilatedScope __Vscope_ibex_simple_system;
    VerilatedScope __Vscope_ibex_simple_system__u_core__u_ibex_tracer;
    VerilatedScope __Vscope_ibex_simple_system__u_ram__u_ram__gen_generic__u_impl_generic;
    
    // CREATORS
    Vibex_simple_system__Syms(Vibex_simple_system* topp, const char* namep);
    ~Vibex_simple_system__Syms() {}
    
    // METHODS
    inline const char* name() { return __Vm_namep; }
    inline bool getClearActivity() { bool r=__Vm_activity; __Vm_activity=false; return r; }
    
} VL_ATTR_ALIGNED(VL_CACHE_LINE_BYTES);

#endif  // guard
