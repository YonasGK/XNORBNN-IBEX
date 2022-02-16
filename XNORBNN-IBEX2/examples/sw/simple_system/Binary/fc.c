#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
	FILE * fd1, *fd2, *fd3, *fd4, *fd5, *fd6, *fd7;
	fd1=fopen("images_array.txt",  "r");
	
	fd2=fopen("labels_array.txt", "r");
	fd3=fopen("conv1.txt", "r");
	fd4=fopen("conv2.txt", "r");
	fd5=fopen("fc1.txt", "r");
	fd6=fopen("fc2.txt", "r");
	fd7=fopen("conv2_out.txt", "r");


	//int fd2=open("../data/out_conv1.txt", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
	int input[28][28];
	 long double input_normalize[28][28];
	 long double conv1_weight[5][3][3]; 
     long double conv1_bias[5]={-1.0000, -1.0000, -1.0000, -0.8826, -0.7437};

	
	 long double conv2_weight[5][5][3][3];
	 long double conv2_bias[5]={-0.9736, -0.4265, -1.0000, -1.0000, -0.9064};

	 long double dense1_weight[125][20];
	 long double dense1_bias[20]={-0.0252,  0.0289, -0.0177,  0.0176,  0.0649,  0.0081, -0.0746, -0.0696,
         0.0604,  0.0310,  0.0171, -0.0489, -0.0820,  0.0781, -0.0850, -0.0446,
         0.0299,  0.0774, -0.0356, -0.0877};
     long double running_mean[20]={-75.2339,   99.7761, -165.5808, -110.5155, -114.7227,  -43.2775,
        -148.8012,   -4.6535,   76.9196,   25.2299,   94.6717,   57.5286,
          80.7664,   -1.2790,  -19.4343,   -3.3384,  -59.7952,   31.3342,
         -20.2263,  104.0416};
     long double running_var[20]={4995.5298,  7035.7417,  6182.3174,  4842.7905,  6379.3081,  7329.4604,
         7160.0430,  5952.4316,  6633.8608,  5961.6646,  5268.3682,  4673.7573,
        10069.2227,  9016.2930,  6760.8721,  7414.4731,  6150.0176,  4995.6523,
         7308.4648,  6004.4062};
     long double gamma[20]={3.4391, 3.7817, 3.4134, 3.0156, 3.7161, 3.2194, 3.1732, 3.8139, 3.4474,
        2.8193, 2.8987, 2.7552, 3.3701, 3.5120, 3.4394, 3.7426, 3.6857, 3.1789,
        3.7071, 3.5791};
     long double beta[20]={ 0.6351,  0.3367, -0.1575,  0.1026,  0.9903,  0.3812,  0.2763,  0.8739,
         1.1584,  0.6321,  1.5625,  0.9964,  2.0253,  0.6402,  1.3102,  0.1043,
         0.7814,  0.4894,  0.1267,  1.1030};
	 long double dense2_weight[20][10];
	 long double dense2_bias[10]={-0.2728, -0.2255,  0.0584,  0.3717, -0.1980,  0.4841, -0.8216, -0.0904,
         0.5350,  0.5646};
	int i,j,k;
	char in[20];
	 long double sum[5];
	
	char label[4];
	char weight_ch[20];
	
	 long double temp1;
	//get weight 1

	//printf("first layer\n");
	for(int i=0; i<5; ++i){
		for(int j=0; j<3; ++j){
			for(int k=0; k<3; ++k){
			
					fgets(weight_ch, 20, fd3);
					sscanf(weight_ch, "%Lf", &temp1);
					conv1_weight[i][k][j]=temp1;
			}
					//printf("%Lf\n", temp1 );
		}
		
	}

	//get weight 2
	//printf("second layer\n");
	for(int i=0; i<5; ++i){
		for(int j=0; j<5; ++j){
			for(int k=0; k<3; ++k){
				for(int l=0; l<3; ++l){
					fgets(weight_ch, 20, fd4);
					sscanf(weight_ch, "%Lf", &temp1);
					conv2_weight[i][j][l][k]=temp1;

					//printf("%Lf\n", temp1 );
				}
			}
		}
		
	}
	long double mean[5];
	long double st=0;
	for(int i=0; i<5; ++i){
		st=0;
		for(int j=0; j<5; ++j){
			for(int k=0; k<3; ++k){
				for(int l=0; l<3; ++l){
					
					st+=conv2_weight[i][j][l][k];

					//printf("%Lf\n", temp1 );
				}
			}
		}
		mean[i]=st/45;
		printf("%Lf\n", mean[i]);
	}

	for(int i=0; i<20; ++i){
		for(int j=0; j<125; ++j){
			
					fgets(weight_ch, 20, fd5);
					sscanf(weight_ch, "%Lf", &temp1);
					dense1_weight[j][i]=temp1;

		}
		
	}
	printf("here\n");
	for(int i=0; i<20; ++i){
		for(int j=0; j<10; ++j){
			
					fgets(weight_ch, 20, fd6);
					sscanf(weight_ch, "%Lf", &temp1);
					dense2_weight[i][j]=temp1;
					//printf("%Lf\n", dense2_weight[j][i]);
		}
		
	}
	
	//read input;
	int correct=0;
	int total=1;
	for(int b=0; b<total; ++b){
		char inn[20];
		long double flatten[125];
		long double conv2_in[5][13][13];
		long double conv2_out_avg[5][5][5];

		for(int i=0; i<125; ++i){

					fgets(inn, 20, fd7);
					sscanf(inn, "%Lf", &temp1);
					
					flatten[i]=(temp1+conv2_bias[i/25]);
					
					
		}
		
		

	 long double layer1_out[20];
  	 long double out[10];
  	 long double out_n[10];


	//compute first layer
	for(int i=0; i<20; ++i){
		layer1_out[i]=0;
		for(int j=0; j<125; ++j){
			layer1_out[i]+=(flatten[j]*dense1_weight[j][i]);
		}
		layer1_out[i]+=dense1_bias[i];
	}
	long double layer1_bn[20];
	 //batch normnalization
	for(int i=0; i<20; i++){
	 	layer1_bn[i]=((layer1_out[i]-running_mean[i])/sqrt(running_var[i]+ 0.00001))*gamma[i] + beta[i];
	 }
	for(int i=0; i<20; ++i){
		if(layer1_bn[i]<0)
			layer1_bn[i]=0.0;
		//printf("%Lf\n", layer1_out[i]);
	}
	 long double sum_d1=0;
	
	 
	//compute second layer
	 long double exp_sum=0.0;
	for(int i=0; i<10; ++i){
		out[i]=0;
		for(int j=0; j<20; ++j){
			out[i]+=(layer1_bn[j]*dense2_weight[j][i]);
		}
		out[i]+=dense2_bias[i];
		

		exp_sum+=exp(out[i]);
		
		}

	//compute softmax
	int max_index=-1;
	long double temp_max;
	temp_max=0.0;
	for(int i=0; i<10; ++i){
		out_n[i]=exp(out[i])/exp_sum;
		if(out_n[i]> temp_max){
			temp_max=out_n[i];
			max_index=i;
		}
		
	}	

		fgets(label, 3, fd2);
		printf("%s", label);
		int Label=atoi(label);
		if(Label==max_index)
			correct++;
		printf("%d -- %Lf\n", max_index, temp_max);
		//printf("-------------------------------\n");

		
		
	}
	fclose(fd1);
	fclose(fd2);
	fclose(fd3);
	fclose(fd4);
	fclose(fd5);
	fclose(fd6);
	fclose(fd7);
	printf("%Lf\n", (long double)correct/total);
	return 0;
	//close(fd2);

}