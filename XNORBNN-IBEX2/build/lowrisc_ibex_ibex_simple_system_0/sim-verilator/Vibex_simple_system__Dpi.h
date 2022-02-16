// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Prototypes for DPI import and export functions.
//
// Verilator includes this file in all generated .cpp files that use DPI functions.
// Manually include this file where DPI .c import functions are declared to ensure
// the C functions match the expectations of the DPI imports.

#include "svdpi.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    
    // DPI EXPORTS
    // DPI export at ../src/lowrisc_ibex_ibex_simple_system_0/rtl/ibex_simple_system.sv:260
    extern long long mhpmcounter_get(int index);
    // DPI export at ../src/lowrisc_prim_util_memload_0/rtl/prim_util_memload.sv:65
    extern int simutil_verilator_get_mem(int index, svBitVecVal* val);
    // DPI export at ../src/lowrisc_prim_util_memload_0/rtl/prim_util_memload.sv:23
    extern void simutil_verilator_memload(const char* file);
    // DPI export at ../src/lowrisc_prim_util_memload_0/rtl/prim_util_memload.sv:46
    extern int simutil_verilator_set_mem(int index, const svBitVecVal* val);
    
#ifdef __cplusplus
}
#endif
