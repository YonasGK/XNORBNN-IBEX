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
	int *input, *conv4_w;
	int input_binary;
	input=(int *)0x00165C20;
	conv4_w=(int *)0x00161DA0;
	int conv4_bin[10][10];
	int conv4_bias[10]={0,0,0,0,0,1,1,1,1,0};
	int i,j,k,l,m,z,o,p;
	

	//binarize conv4 weights
	int *conv4_temp;
	conv4_temp=conv4_w;
	for(i=0; i<10; i++){
		conv4_temp=conv4_w+90*i;
		for(j=0; j<10; j++){
			conv4_bin[i][j]=pack(conv4_temp, 9, 10);
			conv4_temp+=j;
		}
		
	}
	for(z=0; z<1; z++){
		int con_out4[10][8][8]={};
		input_binary=0;
		
		m=0;
		input_binary=0;
		for(k=0; k<10; k++){
			for(i=0; i<8; i++){
				for(j=0; j<8; j++){
					
					//input_binary=pack_inter((int *)con_out3[l], 3, 3, j,i, 10);
					
					m=0;
					for(l=0; l<10; l++){
						input_binary=0;
						for(o=i; o<3+i; o++){
							for (p=j; p<3+j; p++){

							asm volatile(
								"pack	%[z], %[x], %[y]\n\t"
									: [z] "=r" (input_binary)
									: [x] "r" (input_binary), [y] "r" (*(input+(l*64) + (8*o) + p))
								);
							}
						}
						m+=conv_2d_multi(input_binary, conv4_bin[k][l]);
						
					}
					//puthex(m);
					m+=conv4_bias[k];
					
					if(m>45)
						con_out4[k][i][j]=1;
					else
						con_out4[k][i][j]=0;

					
				}
			}
		}
	for(i=0; i<10; i++){
		for(j=0; j<8; j++){
			for(k=0; k<8; k++){
				if(con_out4[i][j][k] == 0)
					putchar('0');
				else
					putchar('1');
			}
		}
	}
	input+=640;

	}
	return 0;

}