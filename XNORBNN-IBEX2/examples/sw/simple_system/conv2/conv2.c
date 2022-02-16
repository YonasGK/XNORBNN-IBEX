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
	int conv1_bin[5][3][3];
	int conv1_bias[5]={-1,-1,-1,-1,-1};
	int i,j,k,l,m,z,o,p,s;
	int *conv1_temp;
	conv1_temp=conv1_w;
	
	int *conv2_w;
	conv2_w=(int *)0x00161DA0;
	int conv2_bin[5][5][3][3];
	int conv2_bias[5]={1,1,1,1,1};
	int *conv2_temp;
	conv2_temp=conv2_w;

	//pack weight1

	for(i=0; i<5; i++){
		for(j=0; j<3; j++){
			for(k=0; k<3; k++){
				
				conv1_bin[i][k][j]=*conv1_temp;
				conv1_temp+=1;
		    //puthex(conv1_bin[i][k][j]);
			}
		}
	}

	//pack weight2

	for(i=0; i<5; i++){
		for(j=0; j<5; j++){
			for(k=0; k<3; k++){
				for(l=0; l<3; l++){
					conv2_bin[i][j][l][l]=*conv2_temp;
					conv2_temp+=1;
		//puthex(conv1_bin[i]);
				}
			}
		}
	}
	//puthex(-1);
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
					
					for(o=0; o<3; o++){
						for (p=0; p<3; p++){
							m+=(*(input+(28*(o+i)) + (p+j))*conv1_bin[l][o][p]);
							
						}
					}
					m+=conv1_bias[l];
					//puthex(m);
					if(i%2==0 && j%2==0)
						con_out1[l][i/2][j/2]=m;
					else if(m > con_out1[l][i/2][j/2])
						con_out1[l][i/2][j/2]=m;
				

				
				}
			}
		}

	input+=784;
	for(i=0; i<5; ++i){
			for(j=0; j<13; ++j){
				for(k=0; k<13; ++k){
					if(con_out1[i][j][k]>0)
						con_out1[i][j][k]=1;
					else if(con_out1[i][j][k]<0)
						con_out1[i][j][k]=-1;
					//printf("%Lf\n",  conv1_out[i][j][k]);

				}
			}
		}
	//puthex(-1);
	int con_out2[5][5][5]={};
	for(s=0; s<5; s++){
			for(i=0; i<10; i++){
				for(j=0; j<10; j++){
					m=0;
					for(p=0; p<5; p++){
						for(l=0; l<3; l++){
							for(o=0; o<3; o++){

								m+=(con_out1[p][i+l][j+o]*conv2_bin[s][p][l][o]);

								//printf("%Lf %Lf\n",input_normalize[i+l][j+m], conv1_weight[l][m] );
							}
						}
						//printf("\n");
						
					}
					
					
					if(m > con_out2[s][i/2][j/2])
						con_out2[s][i/2][j/2]=m;
					//printf("%Lf\n",  tempo);

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