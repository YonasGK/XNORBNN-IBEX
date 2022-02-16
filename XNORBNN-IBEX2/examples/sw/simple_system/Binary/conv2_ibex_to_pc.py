import binascii


binary=open("conv2_out.txt", 'wb')
with open("../../../../ibex_simple_system.log", 'rb') as hexf:
	for row in hexf:
		binary.write(str(int(row, 16)))
		binary.write('\n')