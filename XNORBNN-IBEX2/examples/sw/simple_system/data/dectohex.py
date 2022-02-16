import numpy as np
convn1=open('conv1.txt', 'r')
convn2=open('conv2.txt', 'r')
convn3=open('conv3.txt', 'r')
convn4=open('conv4.txt', 'r')
densen1=open('dense1.txt', 'r')
densen2=open('dense2.txt','r')
dense1_org=open('dense_wdec.txt', 'r')
dense2_org=open('dense2_wdec.txt', 'r')
o_con1=open('out_conv1.txt', 'r')
o_con2=open('out_conv2.txt', 'r')
o_con3=open('out_conv3.txt', 'r')

with open('conv1.vmem','w') as conv1:
	for row in convn1:
		if '-' in row:
			conv1.write('0xffffffff')
			conv1.write('\n')
		else:
			conv1.write('0x1')
			conv1.write('\n')

with open('conv2.vmem','w') as conv2:
	for row in convn2:
		if '-' in row:
			conv2.write('0xffffffff')
			conv2.write('\n')
		else:
			conv2.write('0x1')
			conv2.write('\n')

with open('conv3.vmem','w') as conv3:
	for row in convn3:
		if '-' in row:
			conv3.write('0xffffffff')
			conv3.write('\n')
		else:
			conv3.write('0x1')
			conv3.write('\n')
with open('conv4.vmem','w') as conv4:
	for row in convn4:
		if '-' in row:
			conv4.write('0xffffffff')
			conv4.write('\n')
		else:
			conv4.write('0x1')
			conv4.write('\n')

with open('dense1.vmem','w') as dense1:
	for row in densen1:
		if '-' in row:
			dense1.write('0xffffffff')
			dense1.write('\n')
		else:
			dense1.write('0x1')
			dense1.write('\n')
with open('dense2.vmem','w') as dense2:
	for row in densen2:
		if '-' in row:
			dense2.write('0xffffffff')
			dense2.write('\n')
		else:
			dense2.write('0x1')
			dense2.write('\n')
with open('dense1_hex.vmem', 'w') as dense1_o:
	for row in dense1_org:
		if '-' in row:
			dense1_o.write('0xffffffff')
			dense1_o.write('\n')
		else:
			dense1_o.write('0x1')
			dense1_o.write('\n')
with open('dense2_hex.vmem', 'w') as dense2_o:
	for row in dense2_org:
		if '-' in row:
			dense2_o.write('0xffffffff')
			dense2_o.write('\n')
		else:
			dense2_o.write('0x1')
			dense2_o.write('\n')
with open('i_conv2.vmem', 'w') as i_conv2:
	for row in o_con1:
		if '-' in row:
			i_conv2.write('0xffffffff')
			i_conv2.write('\n')
		else:
			i_conv2.write('0x1')
			i_conv2.write('\n')
with open('i_conv3.vmem', 'w') as i_conv3:
	for row in o_con2:
		if '-' in row:
			i_conv3.write('0xffffffff')
			i_conv3.write('\n')
		else:
			i_conv3.write('0x1')
			i_conv3.write('\n')
with open('i_conv4.vmem', 'w') as i_conv4:
	for row in o_con3:
		if '-' in row:
			i_conv4.write('0xffffffff')
			i_conv4.write('\n')
		else:
			i_conv4.write('0x1')
			i_conv4.write('\n')
