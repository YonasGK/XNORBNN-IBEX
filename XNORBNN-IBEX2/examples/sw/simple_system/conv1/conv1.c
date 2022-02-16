#include "simple_system_common.h"

int pack(int *a, int size, int step){
	int bin_a=-1;
	int i,j;
	for(i=0; i<3; i++){
		
		for (j=0; j<3; j++){
			//puthex(*(a+4*(i+(width+wid_off)+j)));
			//puthex(*((a+i*(width))+j));
			asm volatile(
				"pack	%[z], %[x], %[y]\n\t"
					: [z] "=r" (bin_a)
					: [x] "r" (bin_a), [y] "r" (*((a+j*(3))))
		);
		}
		a+=1;
	}
	return bin_a;
}
int conv_2d_multi1(int act_p, int weight){
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
int conv_2d_multi2(int act_p, int weight){
	int xnor_temp;
	int pack_temp;
	int pcnt_temp;
	asm volatile(
				"and	%[z], %[x], %[y]\n\t"
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
	int *input, *conv1_w;
	int input_binary;
	input=(int *)0x001115D0;
	conv1_w=(int *)0x0015DF20;
	int conv1_bin[5];
	int conv1_bias[5]={-1,-1,-1,-1,-1};
	int i,j,k,l,m,z,o,p;
	int *conv1_temp;
	conv1_temp=conv1_w;
	
	int *conv2_w;
	conv2_w=(int *)0x00161DA0;
	int conv2_bin[5][5];
	int conv2_bias[5]={1,1,1,1,1};
	int *conv2_temp;
	conv2_temp=conv2_w;
	int xnor_temp;
	int pack_temp;
	int pcnt_temp;
	//pack weight1

	for(i=0; i<5; i++){
		conv1_temp=conv1_w+9*i;
		conv1_bin[i]=pack(conv1_temp, 9, 3);
		//puthex(conv1_bin[i]);
		
	}

	//pack weight2

	for(i=0; i<5; i++){
		conv2_temp=(45*i)+conv2_w;
		for(j=0; j<5; j++){
			
			conv2_bin[i][j]=pack(conv2_temp, 9, 3);
			//puthex(conv2_bin[i][j]);
			conv2_temp+=9;
		}
	}

	for(z=0; z<1; z++){
	int con_out1[5][13][13]={};
		input_binary=0;
		 pcount_enable(0);
  		 pcount_reset();
         pcount_enable(1);
		for(l=0; l<5; l++){
			for(i=0; i<26; i++){
				for(j=0; j<26; j++){
					
				
					m=0;
				
					input_binary=0;
					for(o=i; o<3+i; o++){
						for (p=j; p<3+j; p++){

						asm volatile(
							"pack	%[z], %[x], %[y]\n\t"
								: [z] "=r" (input_binary)
								: [x] "r" (input_binary), [y] "r" (*(input+(28*o) + p))
							);
						}
					}
					asm volatile(
							"xnor	%[z], %[x], %[y]\n\t"
								: [z] "=r" (xnor_temp)
								: [x] "r" (input_binary), [y] "r" (conv1_bin[l])
						);
					asm volatile(
							"pcnt	%[z], %[x]\n\t"
								: [z] "=r" (pcnt_temp)
								: [x] "r" (xnor_temp)
						);

						m+=pcnt_temp;

					//m+=conv_2d_multi1(input_binary, conv1_bin[l]);
					m+=conv1_bias[l];
				
				//puthex(m);
					if(m>4)
						con_out1[l][i/2][j/2]=1;
				

				
			}
		}
		}

	input+=784;
	int con_out2[5][5][5]={};
		input_binary=0;
		for(l=0; l<5; l++){
			for(i=0; i<10; i++){
				for(j=0; j<10; j++){
					
				
					m=0;
					for(k=0; k<5; k++){
						input_binary=0;
						for(o=i; o<3+i; o++){
							for (p=j; p<3+j; p++){

							asm volatile(
								"pack	%[z], %[x], %[y]\n\t"
									: [z] "=r" (input_binary)
									: [x] "r" (input_binary), [y] "r" (con_out1[k][o][p])
								);
							}
						}
						asm volatile(
							"xnor	%[z], %[x], %[y]\n\t"
								: [z] "=r" (xnor_temp)
								: [x] "r" (input_binary), [y] "r" (conv2_bin[l][k])
						);
						asm volatile(
							"pcnt	%[z], %[x]\n\t"
								: [z] "=r" (pcnt_temp)
								: [x] "r" (xnor_temp)
						);

						m+=pcnt_temp;
						}

					m=m-(45-m);
					if(m>con_out2[l][i/2][j/2])
						con_out2[l][i/2][j/2]=m;
				

				
				}
			}
		}
		 pcount_enable(0);

	for(i=0; i<5; i++){
		for(j=0; j<5; j++){
			for(k=0; k<5; k++){
				puthex(con_out2[i][j][k]);
				putchar('\n');
			}
		}
	}
	}

	return 0;

}