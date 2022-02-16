#include "simple_system_common.h"
#include <stdlib.h>
#define CONV_FMAP 5
#define IMG_SIZE 28

void pack_test(int *a){
	int bin[25];
	int i,j,k,cnt;
	int temp;
	cnt=0;
	for(i=0; i<IMG_SIZE; i++){
		for (j=0; j<IMG_SIZE; j++){
			//puthex(*(a+4*(i+(width+wid_off)+j)));
			//puthex(*((a+i*(width))+j));
			k=cnt/32;
			temp=*((a+i*(IMG_SIZE))+j)-200;
			asm volatile(
				"pack	%[z], %[x], %[y]\n\t"
					: [z] "=r" (bin[k])
					: [x] "r" (bin[k]), [y] "r" (temp)
		);
			cnt=cnt+1;
			if(cnt%32==0)
				puthex(bin[k]);
		}
	}
}
int pack(int *a[], int length, int width, int len_off, int wid_off){
	int bin_a=0;
	int i,j;
	for(i=len_off; i<length+len_off; i++){
		for (j=wid_off; j<width+wid_off; j++){
			//puthex(*(a+4*(i+(width+wid_off)+j)));
			//puthex(*((a+i*(width))+j));
			asm volatile(
				"pack	%[z], %[x], %[y]\n\t"
					: [z] "=r" (bin_a)
					: [x] "r" (bin_a), [y] "r" (*((a+i*(width))+j))
		);

		}
	}
	return bin_a;
}
int pack_input(int *a, int length, int width, int len_off, int wid_off){
	int bin_a=-1;
	int i,j,temp;
	for(i=len_off; i<length+len_off; i++){
		for (j=wid_off; j<width+wid_off; j++){
			//puthex(*(a+4*(i+(width+wid_off)+j)));
			//puthex(*((a+i*(width))+j));
			temp=*((a+i*(IMG_SIZE))+j);
			//puthex(temp);
			temp=temp-200;
			asm volatile(
				"pack	%[z], %[x], %[y]\n\t"
					: [z] "=r" (bin_a)
					: [x] "r" (bin_a), [y] "r" (temp)
		);
		}
	}
	return bin_a;
}
int conv_2d(int act_p, int weight){
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
	

	if(pcnt_temp > 4){
				// asm volatile(
				// 	"pack	%[z], %[x], %[y]\n\t"
				// 		: [z] "=r" (pack_temp)
				// 		: [x] "r" (pack_temp), [y] "r" (1) 
				// 		);
				return 1;
				}
				else{
					// asm volatile(
					// "pack	%[z], %[x], %[y]\n\t"
					// 	: [z] "=r" (pack_temp)
					// 	: [x] "r" (pack_temp), [y] "r" (0) 
					// 	);
				return 0;
				}
	//puthex(pack_temp);
	//return (pack_temp);

}
int main(){
	int *input;
	int *label;
	int input_binary;
	int conv_weight[5][3][3]={{1,1,1,-1,1,1,-1,-1,1},
							   {-1,-1,-1,1,1,1,1,-1,1},
							   {-1,-1,-1,1,1,1,-1,1,-1},
							   {1,1,1,-1,-1,-1,-1,-1,-1},
								{-1,-1,1,-1,1,1,1,1,-1}};
	int conv_bias[5]={0,0,0,0,0};
	int conv_weight_bin[5];
	
	//int flatten[845];
	
	int *dense1;
	dense1=0x0015DF20;
	int dense1_binary[27][20];
	int dense1_biases[20];
	
	int dense1_out_n[20];
	int *dense2;
	dense2=0x0016E8C0;
	
	int dense2_binary[10];
	int dense2_biases[10]={1,1,-1,-1,1,-1,1,-1,1,1};
	//int out;

	label=0x001110A8;
	input=0x001115D0;
	int i,j,k,l,m,n,z;
	int t1,t2;
	
	int flat_cnt;
	int temp_index;
	//weight binarization for each feature map
	//pack_test(input);
	for(i=0; i<5; i++){
		conv_weight_bin[i]=pack((int **)conv_weight[i], 3, 3, 0,0);
		}
	//dense layer 1 weight binarization
	for (n=0;n<20;n++){
		for (i=0; i<845; i++){
			int temp_index;
			temp_index=i/32;
			int elem=dense1;
			elem=*(dense1+(i*20 + n));
			if(i%32==0)
				dense1_binary[temp_index][n]=-1;
			asm volatile(
				"pack	%[z], %[x], %[y]\n\t"
					: [z] "=r" (dense1_binary[temp_index][n])
					: [x] "r" (dense1_binary[temp_index][n]), [y] "r" (elem)
		
		
		);
				}
			}
//binarize dense2 weigth
	//puthex(a);
	for(i=0; i<10; i++){
		dense2_binary[i]=-1;
		for(j=0; j<20; j++){
			
			int elem;
			elem=*(dense2+(j*10 + i));
			//puthex(elem);
			asm volatile(
			"pack	%[z], %[x], %[y]\n\t"
				: [z] "=r" (dense2_binary[i])
				: [x] "r" (dense2_binary[i]), [y] "r" (elem) 
				);
			}
		}
	
	pcount_enable(0);
  	pcount_reset();
  	pcount_enable(1);
	for(m=0; m<10; m++){
		int out;
		int flatten_binary[27];
		int dense2_out[10];
		int con_out[5][13][13];
		int dense1_out=0;
		int dense1_cnt=0;
		int max=0;
		//convolution + max_pooling
		
  		int temp_c;
		for (i=0; i<26; i++){
			for(j=0; j<26; j++){
				input_binary=pack_input(input, 3,3,i,j);
				for(k=0; k<5; k++){
					temp_c=0;
					//puthex(input_binary);
					t1=i/2;
					t2=j/2;
					z=conv_2d(input_binary, conv_weight_bin[k]);//convolution
					
					asm volatile(
						"or	%[z], %[x], %[y]\n\t"
						: [z] "=r" (temp_c)
						: [x] "r" (temp_c), [y] "r" (z) 
					);
					if(temp_c)
						con_out[k][t1][t2]=z;
					// if(z>con_out[k][t1][t2])
					// 	con_out[k][t1][t2]=z;

				}
			}
		}
		
		//flatten binarized
		flat_cnt=0;
		for(i=0; i<5; i++){
			for (j=0; j<13; j++){
				for(k=0; k<13; k++){
					temp_index=flat_cnt/32;
					//puthex(con_out[k][t1][t2]);
					asm volatile(
						"pack	%[z], %[x], %[y]\n\t"
						: [z] "=r" (flatten_binary[temp_index])
						: [x] "r" (flatten_binary[temp_index]), [y] "r" (con_out[i][j][k])
		
			
		);
					flat_cnt++;
				}
			}
		}
		
		//flatten
		// for(i=0; i<5; i++){
		// 	for (j=0; j<13; j++){
		// 		for(k=0; k<13; k++){
				
		// 			//puthex(con_out[k][t1][t2]);
		// 			flatten[flat_cnt]=con_out[i][j][k];
		// 			flat_cnt++;
		// 		}
		// 	}
		// }
		
		//fully connected layers
		for(i=0; i<20; i++){
			dense1_cnt=0;
			for(j=0; j<27; j++){
				int xnor_temp;
				int pcnt_temp;
				//puthex(flatten_binary[j]);
				asm volatile(
				"xnor	%[z], %[x], %[y]\n\t"
					: [z] "=r" (xnor_temp)
					: [x] "r" (flatten_binary[j]), [y] "r" (dense1_binary[j][i])
			);
				asm volatile(
				"pcnt	%[z], %[x]\n\t"
					: [z] "=r" (pcnt_temp)
					: [x] "r" (xnor_temp)
			);
				dense1_cnt+=pcnt_temp;
			}
				//puthex(dense1_cnt);
				if(dense1_cnt > 442){
					asm volatile(
					"pack	%[z], %[x], %[y]\n\t"
						: [z] "=r" (dense1_out)
						: [x] "r" (dense1_out), [y] "r" (1) 
						);
				}
				else{
					asm volatile(
					"pack	%[z], %[x], %[y]\n\t"
						: [z] "=r" (dense1_out)
						: [x] "r" (dense1_out), [y] "r" (0) 
						);
				}
				
				//puthex(dense1_out);
		}
		

		//fully connected layer
		// for(i=0; i<20; i++){
		// 	dense1_out_n[i]=0;
		// 	for(j=0; j<845; j++){
		// 		dense1_out_n[i]+=(flatten[j]* (*(dense1+j*20+i)));
		// 	}
		// }
		
		//final layer
		for(i=0; i<10; i++){
			int xnor_temp;
			int pcnt_temp;
			
			
			asm volatile(
				"xnor	%[z], %[x], %[y]\n\t"
					: [z] "=r" (xnor_temp)
					: [x] "r" (dense1_out), [y] "r" (dense2_binary[i])
			);
			//puthex(xnor_temp);
				asm volatile(
				"pcnt	%[z], %[x]\n\t"
					: [z] "=r" (pcnt_temp)
					: [x] "r" (xnor_temp)
			);
				pcnt_temp+=dense2_biases[i];
				//puthex(pcnt_temp);
				if(pcnt_temp>max){
					max=pcnt_temp;
					out=i;
				}

		}
		pcount_enable(0);
		//final layer mult
		// int max;
		// for(i=0; i<10; i++){
		// 	for(j=0; j<20; j++){
		// 		dense2_out[i]+=(dense1_out_n[j]*(*(dense2+j*10+i)));
		// 	}
		// 	dense2_out[i]+=dense2_biases[i];
		// 	if(dense2_out[i]>max){
		// 		max=dense2_out[i];
		// 		out=i;
		// 	}
		// 	dense2_out[i]=0;
		// }
		// max=0;
		puthex(out);
		input+=784;
		puthex(*label);
		label+=1;
		max=0;
		out=0;
	}
	

		return 0;

}