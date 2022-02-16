#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
	FILE *fd0, *fd1, *fd2;
	fd0=fopen("out_conv3.txt", "r");
	fd1=fopen("con_out4.txt", "r");
	fd2=fopen("conv4.txt", "r");

	double input[10][10][10];
	double con4_out[10][8][8];
	double weight[10][3][3];
	double out[10][4][4]={};


	char weight_ch[15];
	double weight_avg[10];
	double weight_a;
	double sum_temp[10];
	double temp1;
	for(int i=0; i<10; i++){
		
		for(int j=0; j<90; j++){
			fgets(weight_ch, 15, fd2);
			sscanf(weight_ch, "%lf", &temp1);
			sum_temp[j%10]+=temp1;
		}
		
	}
	
	for(int i=0; i<10; i++){
		weight_avg[i]=sum_temp[i]/90.0;
		sum_temp[i]=0;
	}
	

	for(int z=0; z<1; z++){

	char in[15];
	double temp;
	for(int i=0; i<10; i++){
		for(int j=0; j<8; j++){
			for(int k=0; k<8; k++){
				in[0]=fgetc(fd1);
				in[1]='\0';
		
				if(in[0]=='0'){
			
					con4_out[i][j][k]=-1.0;
				}
				else
					con4_out[i][j][k]=1.0;

		}
	  }
	}
	for(int i=0; i<10; i++){
		for(int j=0; j<10; j++){
			for(int k=0; k<10; k++){
				
			fgets(in, 15, fd0);
			sscanf(in, "%lf", &temp);
			input[i][j][k]=temp;

		}
	  }
	}
	double input_avg[10][8][8];
	double input_a[8][8];
	double s_t;
	for(int i=0; i<10; i++)
		for(int j=0; j<8; j++)
			for(int k=0; k<8; k++){
				s_t=0;
				for(int o=j; o<j+3; o++){
					for(int p=k; p<k+3; p++){
						s_t+=input[i][o][p];
					}
				}
				input_avg[i][j][k]=s_t/9.0;

			}
	for(int i=0; i<8; i++){
		for(int j=0; j<8; j++){
			s_t=0;
			for(int k=0; k<10; k++){
				s_t+=input_avg[k][i][j];

			}
			input_a[i][j]=s_t/10.0;

		}

	}
	
	int t1,t2;
	double max;
	for(int i=0; i<10; i++){
		for(int j=0; j<8; j++){
			for(int k=0; k<8; k++){
				temp=con4_out[i][j][k]*weight_avg[i]*input_a[i][j];
				t1=j/2;
				t2=k/2;
				if(j%2==0 && k%2==0){
					out[i][t1][t2]=temp;
				}
				else{
					if (out[i][t1][t2]<temp)
						out[i][t1][t2]=temp;
					else;
				}


			}
		}




	}
	for(int i=0; i<10; i++){
		for(int j=0; j<4; j++){
			for(int k=0; k<4; k++){
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