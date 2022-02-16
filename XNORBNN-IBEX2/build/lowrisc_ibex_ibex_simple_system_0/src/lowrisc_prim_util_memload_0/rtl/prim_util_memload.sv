// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

/**
 * Memory loader for simulation
 *
 * Include this file in a memory primitive to load a memory array from
 * simulation.
 *
 * Requirements:
 * - A memory array named `mem`.
 * - A parameter `Width` giving the memory width (word size) in bit.
 * - A parameter `Depth` giving the memory depth in words.
 * - A parameter `MemInitFile` with a file path of a VMEM file to be loaded into
*    the memory if not empty.
 */

`ifdef VERILATOR
  // Task for loading 'mem' with SystemVerilog system task $readmemh()
  export "DPI-C" task simutil_verilator_memload;

  task simutil_verilator_memload;
    input string file;
   // $readmemh("/home/yonas/ibex-master/examples/sw/simple_system/data/labels.vmem", mem, 17450);
    //$readmemh("/home/yonas/ibex-master/examples/sw/simple_system/data/img_hex.vmem", mem, 17780);
   $readmemh("/home/yonas/ibex-master/examples/sw/simple_system/Binary/img_hex.vmem", mem, 17780);
    /*$readmemh("/home/yonas/ibex-master/examples/sw/simple_system/data/dense1_hex.vmem", mem, 96200);
    $readmemh("/home/yonas/ibex-master/examples/sw/simple_system/data/dense2_hex.vmem", mem, 113200);*/
   $readmemh("/home/yonas/ibex-master/examples/sw/simple_system/Binary/conv1.vmem", mem, 96200);
     // $readmemh("/home/yonas/ibex-master/examples/sw/simple_system/Binary/conv2.vmem", mem, 96300);
     // $readmemh("/home/yonas/ibex-master/examples/sw/simple_system/data/conv3.vmem", mem, 96600);
   $readmemh("/home/yonas/ibex-master/examples/sw/simple_system/Binary/conv2.vmem", mem, 100200);
      //$readmemh("/home/yonas/ibex-master/examples/sw/simple_system/data/i_conv3.vmem", mem, 101200);
      //$readmemh("/home/yonas/ibex-master/examples/sw/simple_system/data/i_conv4.vmem", mem, 104200);
     // $readmemh("/home/yonas/ibex-master/examples/sw/simple_system/data/i_conv4.vmem", mem, 109000);
    $readmemh(file, mem);
    
   $writememh("/home/yonas/ibex-master/examples/sw/simple_system/data/memory_array.hex", mem);
  endtask

  // Function for setting a specific element in |mem|
  // Returns 1 (true) for success, 0 (false) for errors.
  export "DPI-C" function simutil_verilator_set_mem;

  function int simutil_verilator_set_mem(input int         index,
                                         input bit [255:0] val);

    // Function will only work for memories <= 256 bits
    if (Width > 256) begin
      return 0;
    end

    if (index >= Depth) begin
      return 0;
    end

    mem[index] = val[Width-1:0];
    return 1;
  endfunction

  // Function for getting a specific element in |mem|
  export "DPI-C" function simutil_verilator_get_mem;

  function int simutil_verilator_get_mem(input int          index,
                                         output bit [255:0] val);

    // Function will only work for memories <= 256 bits
    if (Width > 256) begin
      return 0;
    end

    if (index >= Depth) begin
      return 0;
    end

    val = 0;
    val[Width-1:0] = mem[index];
    return 1;
  endfunction
`endif

initial begin
  if (MemInitFile != "") begin : gen_meminit
      $display("Initializing memory %m from file '%s'.", MemInitFile);
      $readmemh(MemInitFile, mem);
      
  end
end
