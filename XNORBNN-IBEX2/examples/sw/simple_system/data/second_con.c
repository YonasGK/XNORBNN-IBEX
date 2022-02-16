#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
	FILE *fd0, *fd1, *fd2;
	fd0=fopen("out_conv1.txt", "r");
	fd1=fopen("con_out2.txt","r");
	fd2=fopen("conv2.txt", "r");

	double input[5][26][26];
	double con2_out[5][24][24];
	double weight[5][45];
	double out[5][12][12]={};

	char weight_ch[15];
	double weight_avg[5];
	double weight_a;
	double sum_temp[5];
	double temp1;
	for(int i=0; i<5; i++){
		
		for(int j=0; j<45; j++){
			fgets(weight_ch, 15, fd2);
			sscanf(weight_ch, "%lf", &temp1);
			sum_temp[j%5]+=temp1;
		}
		
	}
	//sum_temp=0;
	for(int i=0; i<5; i++){
		weight_avg[i]=sum_temp[i]/45.0;
		sum_temp[i]=0;
	}
	

	for(int z=0; z<1; z++){

	char in[15];
	double temp;
	for(int i=0; i<5; i++){
		for(int j=0; j<24; j++){
			for(int k=0; k<24; k++){
				in[0]=fgetc(fd1);
				in[1]='\0';
		
				if(in[0]=='0'){
			
					con2_out[i][j][k]=-1.0;
				}
				else
					con2_out[i][j][k]=1.0;

		}
	  }
	}
	for(int i=0; i<5; i++){
		for(int j=0; j<26; j++){
			for(int k=0; k<26; k++){
				
			fgets(in, 15, fd0);
			sscanf(in, "%lf", &temp);
			input[i][j][k]=temp;

		}
	  }
	}
	double input_avg[5][24][24];
	double input_a[24][24];
	double s_t;
	for(int i=0; i<5; i++)
		for(int j=0; j<24; j++)
			for(int k=0; k<24; k++){
				s_t=0;
				for(int o=j; o<j+3; o++){
					for(int p=k; p<k+3; p++){
						s_t+=input[i][o][p];
					}
				}
				input_avg[i][j][k]=s_t/9.0;

			}

	for(int i=0; i<24; i++){
		for(int j=0; j<24; j++){
			s_t=0;
			for(int k=0; k<5; k++){
				s_t+=input_avg[k][i][j];

			}
			input_a[i][j]=s_t/5.0;

		}

	}

	int t1,t2;
	double max;
	for(int i=0; i<5; i++){
		for(int j=0; j<24; j++){
			for(int k=0; k<24; k++){
				temp=con2_out[i][j][k]*weight_avg[i]*input_a[i][j];
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
	for(int i=0; i<5; i++){
		for(int j=0; j<12; j++){
			for(int k=0; k<12; k++){
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