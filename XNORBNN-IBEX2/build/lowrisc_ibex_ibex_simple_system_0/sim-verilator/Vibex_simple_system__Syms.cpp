// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vibex_simple_system__Syms.h"
#include "Vibex_simple_system.h"



// FUNCTIONS
Vibex_simple_system__Syms::Vibex_simple_system__Syms(Vibex_simple_system* topp, const char* namep)
    // Setup locals
    : __Vm_namep(namep)
    , __Vm_activity(false)
    , __Vm_didInit(false)
    // Setup submodule names
{
    // Pointer to top level
    TOPp = topp;
    // Setup each module's pointers to their submodules
    // Setup each module's pointer back to symbol table (for public functions)
    TOPp->__Vconfigure(this, true);
    // Setup scopes
    __Vscope_ibex_simple_system.configure(this, name(), "ibex_simple_system", "ibex_simple_system", VerilatedScope::SCOPE_OTHER);
    __Vscope_ibex_simple_system__u_core__u_ibex_tracer.configure(this, name(), "ibex_simple_system.u_core.u_ibex_tracer", "u_ibex_tracer", VerilatedScope::SCOPE_OTHER);
    __Vscope_ibex_simple_system__u_ram__u_ram__gen_generic__u_impl_generic.configure(this, name(), "ibex_simple_system.u_ram.u_ram.gen_generic.u_impl_generic", "u_impl_generic", VerilatedScope::SCOPE_OTHER);
    // Setup export functions
    for (int __Vfinal=0; __Vfinal<2; __Vfinal++) {
        __Vscope_ibex_simple_system.exportInsert(__Vfinal, "mhpmcounter_get", (void*)(&Vibex_simple_system::__Vdpiexp_ibex_simple_system__DOT__mhpmcounter_get_TOP));
        __Vscope_ibex_simple_system__u_ram__u_ram__gen_generic__u_impl_generic.exportInsert(__Vfinal, "simutil_verilator_get_mem", (void*)(&Vibex_simple_system::__Vdpiexp_ibex_simple_system__DOT__u_ram__DOT__u_ram__DOT__gen_generic__DOT__u_impl_generic__DOT__simutil_verilator_get_mem_TOP));
        __Vscope_ibex_simple_system__u_ram__u_ram__gen_generic__u_impl_generic.exportInsert(__Vfinal, "simutil_verilator_memload", (void*)(&Vibex_simple_system::__Vdpiexp_ibex_simple_system__DOT__u_ram__DOT__u_ram__DOT__gen_generic__DOT__u_impl_generic__DOT__simutil_verilator_memload_TOP));
        __Vscope_ibex_simple_system__u_ram__u_ram__gen_generic__u_impl_generic.exportInsert(__Vfinal, "simutil_verilator_set_mem", (void*)(&Vibex_simple_system::__Vdpiexp_ibex_simple_system__DOT__u_ram__DOT__u_ram__DOT__gen_generic__DOT__u_impl_generic__DOT__simutil_verilator_set_mem_TOP));
    }
}
