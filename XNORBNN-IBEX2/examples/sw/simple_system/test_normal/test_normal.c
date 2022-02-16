#include "simple_system_common.h"

int main(){
	int input[5][5];
	int filter[3][3];
	int output[3][3];
	int i,j,k,l;
	int z;
	

  	for (i=0; i<3; i++){
  		for(j=0; j<3; j++){
  			filter[i][j]= i-j;
  		}
  	}
    for (i=0; i<5; i++){
      for(j=0; j<5; j++){
        input[i][j]=i+j;
      }
    }
    pcount_enable(0);
    pcount_reset();
    pcount_enable(1);

  	for (i=0;  i<3; i++){
  		for (j=0; j<3; j++){
  			for (k=0; k<3; k++){
  				for (l=0; l<3; l++){
  					//output[i][j]+=input[i+k][j+l]*filter[k][l];
  					asm volatile(
						"mul	%[z], %[x], %[y]\n\t"
							: [z] "=r" (z)
							: [x] "r" (input[i+k][j+l]), [y] "r" (filter[k][l])
						);
  					asm volatile(
						"add	%[z], %[x], %[y]\n\t"
							: [z] "=r" (output[i][j])
							: [x] "r" (output[i][j]), [y] "r" (z)
						);

  				}
  			}
  			//puthex(output[i][j]);
  		}
  	}
  	return 0;

}