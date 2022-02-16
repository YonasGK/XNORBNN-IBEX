import binascii


binary=open("bin_conv1.txt", 'wb')
with open("../../../../ibex_simple_system.log", 'rb') as hexf:
	for row in hexf:
		binary.write(row)
