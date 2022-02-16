#include "simple_system_common.h"

int main(){

	int input[5][5];
  int input_b;
	int filter[3][3];
  int filter_b;
	int output;
	int i,j,k,l,m;
	int z;
	int cnt_out;
  int count; 
  int temp_f;
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
    
    count=0;
    for (i=0; i<3; i++){
      for(j=0; j<3; j++){
        if(filter[i][j] > 0);
        else{
          //temp_f = (0 << count);
          asm volatile(
              "sll %[z], %[x], %[y]\n\t"
              : [z] "=r" (temp_f)
              : [x] "r" (0), [y] "r" (count)
      );
          //filter_b =filter_b & temp_f ;
          asm volatile(
              "and %[z], %[x], %[y]\n\t"
              : [z] "=r" (filter_b)
              : [x] "r" (filter_b), [y] "r" (temp_f)
      );
        }
        temp_f=0;
        count=count+1;
      }
    }
    pcount_enable(0);
    pcount_reset();
    pcount_enable(1);
  cnt_out=0;
  for(i=0; i<3; i++){
    for (j=0; j<3; j++){
      count=0;
      for (l=j; l<3+j; l++){
        for(m=i; m<3+i; m++){
          if(input[l][m] > 0){
             asm volatile(
              "sll %[z], %[x], %[y]\n\t"
              : [z] "=r" (temp_f)
              : [x] "r" (1), [y] "r" (count)
      );
            //temp_f = (0<<count);
           // input_b =input_b |  temp_f;
             asm volatile(
              "or %[z], %[x], %[y]\n\t"
              : [z] "=r" (input_b)
              : [x] "r" (input_b), [y] "r" (temp_f)
      );
          }
        temp_f=0;
        count=count+1;
        }
      }
      //puthex(input_bin);
      asm volatile(
        "xor %[z], %[x], %[y]\n\t"
          : [z] "=r" (k)
          : [x] "r" (input_b), [y] "r" (filter_b)
      );
      asm volatile(
        "not %[z], %[x]\n\t"
          : [z] "=r" (z)
          : [x] "r" (k)
      );
      //puthex(k);
      asm volatile(
        "pcnt %[z], %[x]\n\t"
          : [z] "=r" (l)
          : [x] "r" (z)
    );
      //puthex(l);

      if(l > 4){
        //temp_f=(1<<cnt_out);
        asm volatile(
              "sll %[z], %[x], %[y]\n\t"
              : [z] "=r" (temp_f)
              : [x] "r" (1), [y] "r" (cnt_out)
      );
        //output =output | temp_f;
        asm volatile(
              "or %[z], %[x], %[y]\n\t"
              : [z] "=r" (output)
              : [x] "r" (output), [y] "r" (temp_f)
      );
      }
      temp_f=0;
      cnt_out=cnt_out+1;
    }
  }
  //puthex(output);
  pcount_enable(0);
  return 0;

}