#include "simple_system_common.h"
#include "stdlib.h"

int pack(int *a[], int length, int width, int len_off, int wid_off);
int conv(int *input[], int bin_filter, int length, int width);

int main(){
	pcount_enable(0);
  	pcount_reset();
  	pcount_enable(1);
	int input[5][5];
	int filter[3][3];
	int filter_binarized;
	int output_binary;
	int i,j;
	pcount_enable(0);
  	pcount_reset();
  	pcount_enable(1);

  	//char label1[2];
  	
  	//puthex(label1);

  	for (i=0; i<5; i++){
  		for(j=0; j<5; j++){
  			input[i][j]=i+j;
  		}
  	}
  	for (i=0; i<3; i++){
  		for(j=0; j<3; j++){
  			filter[i][j]= i+j;
  		}
  	}

  	filter_binarized=pack((int **)filter, 3, 3, 0, 0);
  	pcount_enable(0);
  	pcount_reset();
  	pcount_enable(1);
  	//puthex(filter_binarized);
  	output_binary=conv((int **)input, filter_binarized, 3, 3);
  	int *a;
  	a=0x0015DF20;
  	puthex(*a);

	
	pcount_enable(0);
	return 0;
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
int conv(int *input[], int bin_filter, int length, int width){
	int i,j,k,l;
	int input_bin=-1;
	int out_bin=0;
	for(i=0; i<length; i++){
		for (j=0; j<width; j++){
			input_bin=pack((int **)input, length, width, j, i);
			//puthex(input_bin);
			asm volatile(
				"xnor	%[z], %[x], %[y]\n\t"
					: [z] "=r" (k)
					: [x] "r" (input_bin), [y] "r" (bin_filter)
			);
			//puthex(k);
			asm volatile(
				"pcnt	%[z], %[x]\n\t"
					: [z] "=r" (l)
					: [x] "r" (k)
		);
			//puthex(l);
			if(l>4){
				asm volatile(
					"pack	%[z], %[x], %[y]\n\t"
						: [z] "=r" (out_bin)
						: [x] "r" (out_bin), [y] "r" (1)
				);}
			else{
				asm volatile(
					"pack	%[z], %[x], %[y]\n\t"
						: [z] "=r" (out_bin)
						: [x] "r" (out_bin), [y] "r" (0)
				);
			}
			input_bin=0;

		}
	}
	//puthex(out_bin);
	return out_bin;

}