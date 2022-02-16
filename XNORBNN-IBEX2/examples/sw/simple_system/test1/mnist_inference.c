#include "simple_system_common.h"

#define CONV_FMAP 5
#define IMG_SIZE 28

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
int pack_input(int *a[], int length, int width, int len_off, int wid_off){
	int bin_a=0;
	int i,j,temp;
	for(i=len_off; i<length+len_off; i++){
		for (j=wid_off; j<width+wid_off; j++){
			//puthex(*(a+4*(i+(width+wid_off)+j)));
			//puthex(*((a+i*(width))+j));
			temp=*((a+i*(width))+j);
			temp=temp-170;
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

	asm volatile(
				"pack	%[z], %[x], %[y]\n\t"
					: [z] "=r" (pack_temp)
					: [x] "r"  (pack_temp), [y] "r" (pcnt_temp)
		);
	return pack_temp;

}
int main(){
	int *input[];
	int *label;
	int input_binary;
	int conv_weight[5][3][3];
	int conv_weight_bin[5];
	int conv_weight_bin[5];
	int con_out[5][13][13];
	int flatten[845];
	int flatten_binary[27];
	int dense1[845][20];
	int dense1_binary[27][20];
	int dense1_biases[20];
	int dense1_out;
	int dense2[20][10];
	int dense2_bias[10];
	int dense2_binary[10];
	int out;

	input=0x00100000;
	label=0x00100000;
	int i,j,k,l,m,n;
	for(m=0; m<313; m++){
		//weight binarization for each feature map
		for(i=0; i<5; i++){
			conv_weight_bin[i]=pack(conv_weight[i], 3, 3, 0,0);
		}
		//convloution + max_pooling
		for (i=0; i<IMG_SIZE-2; i++){
			for(j=0; j<IMG_SIZE-2; j++){
				for(k=0; k<5; k++){
					input_binary=pack_input(input, 3,3,j,i)
					con_out[k][i/2][j/2]|=conv_2d(input_binary, conv_weight_bin[k])//convolution + max_pooling
				}
			}
		}
		//dense layer 1 weight binarization
		for (n=0;n<20;n++)
			for (i=0; i<845; i++){
						int temp_index;
						temp_index=i/32;
						asm volatile(
							"pack	%[z], %[x], %[y]\n\t"
							: [z] "=r" (dense1_binary[temp_index][n])
							: [x] "r" (dense1_binary[temp_index][n]), [y] "r" (dense1[i][n])
		);
				}
		//flatten
		for(i=0; i<5; i++)
			for (j=0; j<13, j++)
				for(k=0; k<13; k++){
					int temp_index=(i*j + k)/32;
					asm volatile(
						"pack	%[z], %[x], %[y]\n\t"
						: [z] "=r" (flatten_binary[temp_index])
						: [x] "r" (flatten_binary[temp_index]), [y] "r" (con_out[i][j][k])
		);
				}


		//fully connected layers
		for(i=0; i<20; i++){
			for(j=0; j<27; j++){
				int xnor_temp;
				int pcnt_temp;
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
				asm volatile(
				"pack	%[z], %[x], %[y]\n\t"
					: [z] "=r" (dense1_out)
					: [x] "r" (dense1_out), [y] "r" (xnor_temp) 
					);


			}
		}
		//binarize dense2 weigth
		for(i=0; i<10; i++)
			for(j=0; j=20; j++){
				asm volatile(
				"pack	%[z], %[x], %[y]\n\t"
					: [z] "=r" (dense2_binary[i])
					: [x] "r" (dense2_binary[i]), [y] "r" (dense2[i][j]) 
					);
			}
		//final layer
		for(i=0; i<10; i++){
			int xnor_temp;
			int pcnt_temp;
			asm volatile(
				"xnor	%[z], %[x], %[y]\n\t"
					: [z] "=r" (xnor_temp)
					: [x] "r" (dense1_out), [y] "r" (dense2_binary[i])
			);
				asm volatile(
				"pcnt	%[z], %[x]\n\t"
					: [z] "=r" (pcnt_temp)
					: [x] "r" (xnor_temp)
			);
				asm volatile(
				"pack	%[z], %[x], %[y]\n\t"
					: [z] "=r" (out)
					: [x] "r" (out), [y] "r" (xnor_temp) 
					);


		}

		puthex(out);






}