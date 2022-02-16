#!/bin/bash

cd examples/sw/simple_system/data

./first > out_conv1.txt
python dectohex.py
cd ../../../../

fusesoc --cores-root=. run --target=sim --setup --build lowrisc:ibex:ibex_simple_system --RV32M=1 --RV32E=0 --RV32B=1 --MultiplierImplementation=fast

./build/lowrisc_ibex_ibex_simple_system_0/sim-verilator/Vibex_simple_system --meminit=ram,./examples/sw/simple_system/conv2/conv2.vmem

cd examples/sw/simple_system/data/

python con_out2.py

./second >out_conv2.txt

python dectohex.py
cd ../../../../

fusesoc --cores-root=. run --target=sim --setup --build lowrisc:ibex:ibex_simple_system --RV32M=1 --RV32E=0 --RV32B=1 --MultiplierImplementation=fast
./build/lowrisc_ibex_ibex_simple_system_0/sim-verilator/Vibex_simple_system --meminit=ram,./examples/sw/simple_system/conv3/conv3.vmem

cd examples/sw/simple_system/data/

python con_out3.py
./third > out_conv3.txt

python dectohex.py
cd ../../../../

fusesoc --cores-root=. run --target=sim --setup --build lowrisc:ibex:ibex_simple_system --RV32M=1 --RV32E=0 --RV32B=1 --MultiplierImplementation=fast
./build/lowrisc_ibex_ibex_simple_system_0/sim-verilator/Vibex_simple_system --meminit=ram,./examples/sw/simple_system/conv4/conv4.vmem

cd examples/sw/simple_system/data/

python con_out4.py
./fourth > out_conv4.txt

./last
