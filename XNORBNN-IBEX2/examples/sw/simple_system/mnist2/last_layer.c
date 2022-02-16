#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	double input[160];
	double layer1[160][20];
	double layer1_out[20];
	double layer2[20][10];
	double out[10];
	double out_n[10];
	double layer1_bias[20];
	double layer2_bias[10]={-0.07944726, -0.16064465 ,-0.17467539
,0.053403314,-0.20265327,-0.32476634 ,-0.48430938 ,0.5435659 ,0.5765111};
	char in[15];
	char weights1[15];
	char weights2[15];
	char label[4];
	FILE *fd0;
	FILE *fd1;
	FILE *fd2;
	FILE *fd3;
	fd0=fopen("out_conv4.txt", "r");
	fd1=fopen("dense1.txt",  "r");
	fd2=fopen("dense2.txt",  "r");
	fd3=fopen("labels_array.txt", "r");
	double temp;
	//get layer1 weights and bias
	for(int i=0; i<20; i++){
		for(int j=0; j<160; j++){
			
			fgets(weights1, 15, fd1);
			sscanf(weights1, "%lf", &temp);
			layer1[j][i]=temp;
			
		}
	}
	for(int i=0; i<20; i++){
		fgets(weights1, 15, fd1);
		sscanf(weights1, "%lf", &temp);
		layer1_bias[i]=temp;
		
	}
		//get layer2 weight;
	for(int i=0; i<10; i++){
		for(int j=0; j<20; j++){
			
			fgets(weights2, 15, fd2);
			sscanf(weights2, "%lf", &temp);
			layer2[j][i]=temp;
			
		
		}
	}
  for(int z=0; z<10; z++){
  	//get neurons
  	double temp_in;
	for(int i=0; i<160; i++){
		fgets(in, 15, fd0);
		sscanf(in, "%lf", &temp_in);
		input[i]=temp_in;
		
	}

	//compute first layer
	for(int i=0; i<20; i++){
		layer1_out[i]=0;
		for(int j=0; j<160; j++){
			layer1_out[i]+=(input[j]*layer1[j][i]);
		}
		layer1_out[i]+=layer1_bias[i];
	}
	//compute second layer
	double exp_sum=0.0;
	for(int i=0; i<10; i++){
		out[i]=0;
		for(int j=0; j<20; j++){
			out[i]+=(layer1_out[j]*layer2[j][i]);
		}
		out[i]+=layer2_bias[i];
		exp_sum+=exp(out[i]);
		
		}

	//computer softmax
	for(int i=0; i<10; i++){
		out_n[i]=exp(out[i])/exp_sum;
		printf("%d -- %lf\n", i, out_n[i]);
	}	
		fgets(label, 3, fd3);
		printf("%s", label);
		printf("-------------------------------\n");
	
	}
	fclose(fd0);
	fclose(fd1);
	fclose(fd2);
	fclose(fd3);
	return 0;
}