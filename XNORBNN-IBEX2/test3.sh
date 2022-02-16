cd examples/sw/simple_system/Binary

./input > img_hex.txt
python dectohex.py
cd ../../../../

fusesoc --cores-root=. run --target=sim --setup --build lowrisc:ibex:ibex_simple_system --RV32M=1 --RV32E=0 --RV32B=1 --MultiplierImplementation=fast

./build/lowrisc_ibex_ibex_simple_system_0/sim-verilator/Vibex_simple_system --meminit=ram,./examples/sw/simple_system/conv2/conv2.vmem

cd examples/sw/simple_system/Binary/

python conv2_ibex_to_pc.py
gcc -o fc fc.c -lm
./fc