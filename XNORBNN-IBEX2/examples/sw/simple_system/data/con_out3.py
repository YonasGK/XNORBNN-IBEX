import binascii


binary=open("con_out3.txt", 'wb')
with open("../../../../ibex_simple_system.log", 'rb') as hexf:
	for row in hexf:
		binary.write(row)