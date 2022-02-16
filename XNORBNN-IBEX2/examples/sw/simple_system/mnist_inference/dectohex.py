import numpy as np

dense1=open('dense1_wdec.txt')
dense2=open('dense2_wdec.txt')
dense1_hex=open('dense1_hex.vmem','w')
dense2_hex=open('dense2_hex.vmem','w')

for row in dense1:
	dense1_hex.write(hex(row))
	dense1_hex.write('\n')

for row in dense2:
	dense2_hex.write(hex(row))
	dense2_hex.write('\n')