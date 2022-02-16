#include "simple_system_common.h"

int pack(int *a, int size, int step){
	int bin_a=-1;
	int i;
	for(i=0; i<size; i++){
		
			//puthex(*(a+4*(i+(width+wid_off)+j)));
			//puthex(*((a+i*(width))+j));
			asm volatile(
				"pack	%[z], %[x], %[y]\n\t"
					: [z] "=r" (bin_a)
					: [x] "r" (bin_a), [y] "r" (*((a+i*(step))))
		);

	}
	return bin_a;
}
int pack_input(int *a, int length, int width, int len_off, int wid_off, int size){
	int bin_a=0;
	int i,j,temp;
	for(i=len_off; i<length+len_off; i++){
		for (j=wid_off; j<width+wid_off; j++){
			//puthex(*(a+4*(i+(width+wid_off)+j)));
			//puthex(*((a+i*(width))+j));
			temp=*((a+i*(size))+j);
			//puthex(temp);
			temp=temp-100;
			asm volatile(
				"pack	%[z], %[x], %[y]\n\t"
					: [z] "=r" (bin_a)
					: [x] "r" (bin_a), [y] "r" (temp)
		);
		}
	}
	return bin_a;
}
int pack_inter(int *a, int length, int width, int len_off, int wid_off, int size){
	int bin_a=-1;
	int i,j,temp;
	for(i=len_off; i<length+len_off; i++){
		for (j=wid_off; j<width+wid_off; j++){
			//puthex(*(a+4*(i+(width+wid_off)+j)));
			//puthex(*((a+i*(width))+j));
			temp=(*((a+i*(size))+j));
			//puthex(temp);
			//temp=temp-200;
			asm volatile(
				"pack	%[z], %[x], %[y]\n\t"
					: [z] "=r" (bin_a)
					: [x] "r" (bin_a), [y] "r" (temp)
		);
		}
	}
	return bin_a;
}
int conv_2d(int act_p, int weight, int bias){
	int xnor_temp;
	int pack_temp;
	int pcnt_temp;
	asm volatile(
				"xnor	%[z], %[x], %[y]\n\t"
					: [z] "=r" (xnor_temp)
					: [x] "r" (act_p), [y] "r" (weight)
			);
	asm volatile(
				"pcnt	%[z], %[x]\n\t"
					: [z] "=r" (pcnt_temp)
					: [x] "r" (xnor_temp)
		);
	
	pcnt_temp+=bias;
	if(pcnt_temp > 4){
				return 1;
				// asm volatile(
				// 	"pack	%[z], %[x], %[y]\n\t"
				// 		: [z] "=r" (pack_temp)
				// 		: [x] "r" (pack_temp), [y] "r" (1) 
				// 		);
				 }
				else{
					return -1;
					// asm volatile(
					// "pack	%[z], %[x], %[y]\n\t"
					// 	: [z] "=r" (pack_temp)
					// 	: [x] "r" (pack_temp), [y] "r" (0) 
					// 	);
				}
	//puthex(pack_temp);
	//return (pack_temp);

}
int conv_2d_multi(int act_p, int weight){
	int xnor_temp;
	int pack_temp;
	int pcnt_temp;
	asm volatile(
				"xnor	%[z], %[x], %[y]\n\t"
					: [z] "=r" (xnor_temp)
					: [x] "r" (act_p), [y] "r" (weight)
			);
	asm volatile(
				"pcnt	%[z], %[x]\n\t"
					: [z] "=r" (pcnt_temp)
					: [x] "r" (xnor_temp)
		);
	return pcnt_temp;

}
int main(){
	int i,j,k,l,m,n,z, o,p;
	int *input, *label, *conv1, *conv2, *conv3,*conv4;
	int *dense1, *dense2;
	label=(int *)0x001110A8;
	input=(int *)0x001115D0;
	//input+=784;
	//label+=1;
	conv1=(int *)0x0015DF20;
	conv2=(int *)0x0015E0B0;
	conv3=(int *)0x0015E560;
	conv4=(int *)0x00161DA0;
	dense1=(int *)0x00162D40;
	dense2=(int *)0x00165C20;

	int conv1_bin[5];
	int conv2_bin[5][5];
	int conv3_bin[10][5];
	int conv4_bin[10][10];
	int conv1_bias[5]={1,0,1,0,0};
	int conv2_bias[5]={0,0,1,0,0};
	int conv3_bias[10]={0,1,0,1,0,1,1,1,0,1};
	int conv4_bias[10]={0,0,0,0,0,1,1,1,1,0};
	int dense1_bin[5][20];
	int dense2_bin[10];
	//int dense1_bias[20];
	int dense2_bias[10]={0,1,0,0,1,0,0,0,1,1};
	int out;
	int max;
	//binarize conv1 weights
	for(i=0; i<5; i++){
		conv1_bin[i]=pack(conv1, 9, 1);
		conv1+=9;
	}

	//binarize conv2 weights
	int *conv2_temp;
	conv2_temp=conv2;
	for(i=0; i<5; i++){
		conv2_temp=conv2+45*i;
		for(j=0; j<5; j++){
			conv2_bin[i][j]=pack(conv2_temp, 9, 5);
			//puthex(conv2_bin[i][j]);
			conv2_temp+=j;
		}
		
	}

	//binarize conv3 weights
	int *conv3_temp;
	conv3_temp=conv3;
	for(i=0; i<10; i++){
		conv3_temp=conv3+45*i;
		for(j=0; j<5; j++){
			conv3_bin[i][j]=pack(conv3_temp, 9, 5);
			conv3_temp+=j;
		}
		
	}

	//binarize conv4 weights
	int *conv4_temp;
	conv4_temp=conv4;
	for(i=0; i<10; i++){
		conv4_temp=conv4+90*i;
		for(j=0; j<10; j++){
			conv4_bin[i][j]=pack(conv4_temp, 9, 10);
			conv4_temp+=j;
		}
		
	}

	//binarize the dense1
	int elem;
	int temp_index;
	temp_index=0;
	for (n=0;n<20;n++){
		for (i=0; i<160; i++){
			
			elem=*(dense1+(i*20 + n));
			if(i%32==0){
			 	dense1_bin[temp_index][n]=-1;
			 	if(i!=0)
			 		temp_index+=1;
			}
			asm volatile(
				"pack	%[z], %[x], %[y]\n\t"
					: [z] "=r" (dense1_bin[temp_index][n])
					: [x] "r" (dense1_bin[temp_index][n]), [y] "r" (elem)
			
			);
				}
			}

	//binarize dense 2
	int cnt;
	cnt=0;
	for (i=0; i<10; i++){
		dense2_bin[i]=-1;
		for(j=0; j<20; j++){
			elem=*(dense2+cnt);
			asm volatile(
				"pack	%[z], %[x], %[y]\n\t"
					: [z] "=r" (dense2_bin[i])
					: [x] "r" (dense2_bin[i]), [y] "r" (elem)
		
		
		);
		cnt+=1;
		}
	}
	pcount_enable(0);
  	pcount_reset();
  	pcount_enable(1);
  	int input_binary;
	for(z=0; z<10; z++){
		// int con_out1[5][26][26]={};
		
		// max=0;
		// out=0;
		// input_binary=0;
		// //first layer convolution
		// for (i=0; i<26; i++){
		// 	for(j=0; j<26; j++){
		// 		input_binary=pack_input(input, 3,3,i,j, 28);
		// 		for(k=0; k<5; k++){
					
		// 			con_out1[k][i][j]=conv_2d(input_binary, conv1_bin[k], conv1_bias[k]);//convolution
		// 			//puthex(con_out1[k][i][j]);
		// 		}
		// 	}
		// }
		//second layer convolution + max_pooling
		int con_out2[5][12][12]={};
		int t1,t2;
		input_binary=0;
		for(k=0; k<5; k++){
			for(i=0; i<24; i++){
				for(j=0; j<24; j++){
					t1=i/2;
					t2=j/2;
					//input_binary=pack_inter((int *)con_out1[l], 3, 3, j,i, 26);
					
					m=0;
					for(l=0; l<5; l++){
						input_binary=0;
						for(o=i; o<3+i; o++){
							for (p=j; p<3+j; p++){

							asm volatile(
								"pack	%[z], %[x], %[y]\n\t"
									: [z] "=r" (input_binary)
									: [x] "r" (input_binary), [y] "r" (*(input+(l*676) + (26*o) + p))
								);
							}
							// puthex(*(input+(l*676) + (26*o) + p));
							// putchar('\n');
						}
						

						m+=conv_2d_multi(input_binary, conv2_bin[k][l]);
						
					}
					//puthex(m);
					m+=conv2_bias[k];
					
					//puthex(m);
					if(m>22){
						con_out2[k][t1][t2]=1;

					}
					
		}
	}
	}


		m=0;
		//third layer conv
		input_binary=0;
		int con_out3[10][10][10]={};
		for(k=0; k<10; k++){
			for(i=0; i<10; i++){
				for(j=0; j<10; j++){
					//input_binary=pack_inter((int *)con_out2[l], 3, 3, j,i, 12);
					
					m=0;
					for(l=0; l<5; l++){
						input_binary=0;
						for(o=i; o<3+i; o++){
							for (p=j; p<3+j; p++){

							asm volatile(
								"pack	%[z], %[x], %[y]\n\t"
									: [z] "=r" (input_binary)
									: [x] "r" (input_binary), [y] "r" (con_out2[l][o][p])
								);
							}
						}
						m+=conv_2d_multi(input_binary, conv3_bin[k][l]);
						
					}
					m+=conv3_bias[k];
					
					if(m>22){
						con_out3[k][i][j]=1;
					}
					else
						con_out3[k][i][j]=0;
					
		}
	}

	}
	//fourth layer conv +max pooling
	int con_out4[10][4][4]={};
	int t3,t4;
	m=0;
	input_binary=0;
	for(k=0; k<10; k++){
			for(i=0; i<8; i++){
				for(j=0; j<8; j++){
					t3=i/2;
					t4=j/2;
					//input_binary=pack_inter((int *)con_out3[l], 3, 3, j,i, 10);
					
					m=0;
					for(l=0; l<10; l++){
						input_binary=0;
						for(o=i; o<3+i; o++){
							for (p=j; p<3+j; p++){

							asm volatile(
								"pack	%[z], %[x], %[y]\n\t"
									: [z] "=r" (input_binary)
									: [x] "r" (input_binary), [y] "r" (con_out3[l][o][p])
								);
							}
						}
						m+=conv_2d_multi(input_binary, conv4_bin[k][l]);
						
					}
					//puthex(m);
					m+=conv4_bias[k];
					
					if(m>45){
						con_out4[k][t3][t4]=1;

					}
					
				}
			}
		}
	//flatten
	int flatten_bin[5];
	int count;
	int temp;
	count=0;
	temp=0;
	for(i=0; i<10; i++){
		for(j=0; j<4; j++){
			for(k=0; k<4; k++){
					
				// asm volatile(
				// 			"pack	%[z], %[x], %[y]\n\t"
				// 			: [z] "=r" (flatten_bin[temp])
				// 			: [x] "r" (flatten_bin[temp]), [y] "r" (con_out4[i][j][k])
		
				// 			);
				// count+=1;
				// if(count%32==0)
				// 	temp+=1;
				// 	flatten_bin[temp]=0;
				if(con_out4[i][j][k] == 0)
					putchar('0');
				else
					putchar('1');
			}
		}
	}

		//dense1
		// int dense1_cnt;
		// int dense1_out;
		// dense1_out=0;
		// for(i=0; i<20; i++){
		// 	dense1_cnt=0;
		// 	for(j=0; j<5; j++){
		// 		int xnor_temp;
		// 		int pcnt_temp;
		// 		xnor_temp=0;
		// 		pcnt_temp=0;
		// 		//puthex(flatten_binary[j]);
		// 		asm volatile(
		// 		"xnor	%[z], %[x], %[y]\n\t"
		// 			: [z] "=r" (xnor_temp)
		// 			: [x] "r" (flatten_bin[j]), [y] "r" (dense1_bin[j][i])
		// 	);
		// 		asm volatile(
		// 		"pcnt	%[z], %[x]\n\t"
		// 			: [z] "=r" (pcnt_temp)
		// 			: [x] "r" (xnor_temp)
		// 	);
		// 		dense1_cnt+=pcnt_temp;
		// 	}
				
		// 		if(dense1_cnt > 80){
		// 			asm volatile(
		// 			"pack	%[z], %[x], %[y]\n\t"
		// 				: [z] "=r" (dense1_out)
		// 				: [x] "r" (dense1_out), [y] "r" (1) 
		// 				);
		// 		}
		// 		else{
		// 			asm volatile(
		// 			"pack	%[z], %[x], %[y]\n\t"
		// 				: [z] "=r" (dense1_out)
		// 				: [x] "r" (dense1_out), [y] "r" (0) 
		// 				);
		// 		}
				
				
		// }
		// //puthex(dense1_out);
		// //dense2
		// for(i=0; i<10; i++){
		// 	int xnor_temp;
		// 	int pcnt_temp;
			
			
		// 	asm volatile(
		// 		"xnor	%[z], %[x], %[y]\n\t"
		// 			: [z] "=r" (xnor_temp)
		// 			: [x] "r" (dense1_out), [y] "r" (dense2_bin[i])
		// 	);
		// 	//puthex(xnor_temp);
		// 		asm volatile(
		// 		"pcnt	%[z], %[x]\n\t"
		// 			: [z] "=r" (pcnt_temp)
		// 			: [x] "r" (xnor_temp)
		// 	);
		// 		//pcnt_temp+=dense2_biases[i];
				
		// 		pcnt_temp+=dense2_bias[i];
		// 		//puthex(pcnt_temp);
		// 		if(pcnt_temp>max){
		// 			max=pcnt_temp;
		// 			out=i;
		// 		}

		// }
		//puthex(*label);
		//puthex(out);
		input+=3380;
		label+=1;
		//out=0;
		//max=0;

}
	pcount_enable(0);
	return 0;

}