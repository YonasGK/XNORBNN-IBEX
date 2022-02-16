#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(){
	FILE * fd1, *fd_w;
	
	fd1=fopen("images_array.txt",  "r");
	
	int input[28][28];
	long double input_normalize[28][28];
	long double temp1;
	int total=100;
	for(int b=0; b<total; ++b){
		
		
		char in[20];

		for(int i=0; i<28; ++i){
			for(int j=0; j<28; ++j){
				
				fgets(in, 20, fd1);
				
				input[i][j]=atoi(in);
				//printf("%d ", input[i][j]);
			}
			//printf("\n");
		}	
		//normalize
		long double tt;
		for(int i=0; i<28; ++i){  
			for(int j=0; j<28; ++j){
				
				tt=((input[i][j]/255)-0.1307)/0.3081;
				
				if(tt>0)
					input_normalize[i][j]=-1;
				else if(tt==0)
					input_normalize[i][j]=0;
				else
					input_normalize[i][j]=1;
				printf("%Lf\n", input_normalize[i][j]);
				
			}
			//printf("\n");
		}
	}
	fclose(fd1);
	return 0;
}