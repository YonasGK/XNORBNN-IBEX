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
	int *input, *conv3_w;
	int input_binary;
	input=(int *)0x00162D40;
	conv3_w=(int *)0x0015E560;
	int conv3_bin[10][5];
	int conv3_bias[10]={0,1,0,1,0,1,1,1,0,1};
	int i,j,k,l,m,z,o,p;

	

	//binarize conv3 weights
	int *conv3_temp;
	conv3_temp=conv3_w;
	for(i=0; i<10; i++){
		conv3_temp=conv3_w+45*i;
		for(j=0; j<5; j++){
			conv3_bin[i][j]=pack(conv3_temp, 9, 5);
			conv3_temp+=j;
		}
		
	}
	for(z=0; z<1; z++){
	int con_out3[10][10][10]={};
		input_binary=0;
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
									: [x] "r" (input_binary), [y] "r" (*(input+(l*144) + (12*o) + p))
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

	for(i=0; i<10; i++){
		for(j=0; j<10; j++){
			for(k=0; k<10; k++){
				if(con_out3[i][j][k] == 0)
					putchar('0');
				else
					putchar('1');
			}
		}
	}
	input+=720;

	}
	return 0;

}