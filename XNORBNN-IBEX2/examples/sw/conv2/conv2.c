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
	int *input, *conv2_w;
	int input_binary;
	input=(int *)0x001115D0;
	conv2_w=(int *)0x0015E0B0;
	int conv2_bin[5][5];
	int conv2_bias[5]={0,0,1,0,0};
	int i,j,k,l,m,z,o,p;
	int *conv2_temp;
	conv2_temp=conv2_w;
	
	//binarize weight2

	for(i=0; i<5; i++){
		conv2_temp=conv2_w+45*i;
		for(j=0; j<5; j++){
			conv2_bin[i][j]=pack(conv2_temp, 9, 5);
			//puthex(conv2_bin[i][j]);
			conv2_temp+=j;
		}
		
	}
	for(z=0; z<1; z++){
	int con_out2[5][24][24]={};
		input_binary=0;
		for(k=0; k<5; k++){
			for(i=0; i<24; i++){
				for(j=0; j<24; j++){
					
					
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
						}
						

						m+=conv_2d_multi(input_binary, conv2_bin[k][l]);
						
					}
					//puthex(m);
					m+=conv2_bias[k];
					
					//puthex(m);
					if(m>22)
						con_out2[k][i][j]=1;
					else
						con_out2[k][i][j]=0;

					
				}
			}
		}

	for(i=0; i<5; i++){
		for(j=0; j<24; j++){
			for(k=0; k<24; k++){
				if(con_out2[i][j][k] == 0)
					putchar('0');
				else
					putchar('1');
			}
		}
	}
	input+=3380;

	}
	return 0;

}