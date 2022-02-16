import numpy as np
img_hex=open('img_hex.txt', 'r')
convn1=open('conv1.txt', 'r')
convn2=open('conv2.txt', 'r')




with open('img_hex.vmem','w') as img:
	for row in img_hex:
		if '-' in row:
			img.write('0xffffffff')
			img.write('\n')
		else:
			img.write('0x1')
			img.write('\n')



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
