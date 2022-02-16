#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
	FILE *fd0, *fd1, *fd2;
	fd0=fopen("out_conv2.txt", "r");
	fd1=fopen("con_out3.txt","r");
	fd2=fopen("conv3.txt", "r");

	double input[5][12][12];
	double con3_out[10][10][10];
	double weight[10][3][3];
	double out[10][10][10]={};

	char in[15];
	char weight_ch[15];
	double weight_avg[10];
	double weight_a;
	double sum_temp;
	double temp1;
	for(int i=0; i<10; i++){
		sum_temp=0;
		for(int j=0; j<45; j++){
			fgets(weight_ch, 15, fd2);
			sscanf(weight_ch, "%lf", &temp1);
			sum_temp+=temp;
		}
		weight_avg[i]=sum_temp/45.0;
	}
	sum_temp=0;
	for(int i=0; i<10; i++){
		sum_temp+=weight_avg[i];
	}
	weight_a=sum_temp/10.0;

	for(int z=0; z<10; z++){
	double temp;

	for(int i=0; i<10; i++){
		for(int j=0; j<10; j++){
			for(int k=0; k<10; k++){
				in[0]=fgetc(fd1);
				in[1]='\0';
		
				if(in[0]=='0'){
			
					con3_out[i][j][k]=-1.0;
				}
				else
					con3_out[i][j][k]=1.0;

		}
	  }
	}
	for(int i=0; i<5; i++){
		for(int j=0; j<12; j++){
			for(int k=0; k<12; k++){
				
			fgets(in, 15, fd0);
			sscanf(in, "%lf", &temp);
			input[i][j][k]=temp;

		}
	  }
	}
	double input_avg[10][8][8];
	double s_t;
	for(int i=0; i<10; i++)
		for(int j=0; j<10; j++)
			for(int k=0; k<10; k++){
				s_t=0;
				for(int o=i; o<i+3; o++){
					for(int p=j; p<j+3; p++){
						s_t+=input[i][o][p];
					}
				}
				input_avg[i][j][k]=s_t/9.0;

			}

	
	int t1,t2;
	double max;
	for(int i=0; i<10; i++){
		for(int j=0; j<10; j++){
			for(int k=0; k<10; k++){
				temp=con3_out[i][j][k]*weight_avg[i]*input_avg[i][j][k];
				out[i][j][k]=temp;
				printf("%lf\n", out[i][j][k]);
			}
		}




	}
}	
	fclose(fd0);
	fclose(fd1);
	fclose(fd2);
	return 0;







}