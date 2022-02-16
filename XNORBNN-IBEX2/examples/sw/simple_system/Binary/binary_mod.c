#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
	FILE * fd1, *fd2, *fd3, *fd4, *fd5, *fd6;
	fd1=fopen("images_array.txt",  "r");
	
	fd2=fopen("labels_array.txt", "r");
	fd3=fopen("conv1.txt", "r");
	fd4=fopen("conv2.txt", "r");
	fd5=fopen("fc1.txt", "r");
	fd6=fopen("fc2.txt", "r");


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
	 long double mean[5];
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
	int total=100;
	for(int b=0; b<total; ++b){
		
		 long double conv1_out[5][13][13]={};
		 long double conv2_out[5][5][5]={};
		 long double conv3_out[16][16]={};
		 long double conv4_out[12][12]={};
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
				//printf("%Lf  ", tt);
				
			}
			//printf("\n");
		}


		//conv1
		
		long double tempo=0;
		for(int p=0; p<5; ++p){
		for(int i=0; i<26; ++i){
			for(int j=0; j<26; ++j){
				
					tempo=0;
					for(int l=0; l<3; ++l){
						for(int m=0; m<3; ++m){
							tempo+=(input_normalize[i+l][j+m]*conv1_weight[p][l][m]);
							//printf("%Lf %Lf\n",input_normalize[i+l][j+m], conv1_weight[l][m] );
							//printf("%d %d * %d %d %d\n", i+l, j+m, p, l, m);
						}
					}
					//printf("\n");
					tempo+=conv1_bias[p];
					if(i%2==0 && j%2==0)
						conv1_out[p][i/2][j/2]=tempo;
					else if(tempo > conv1_out[p][i/2][j/2])
						conv1_out[p][i/2][j/2]=tempo;

				}
			}
		}
		



		//conv2
		for(int i=0; i<5; ++i){
			for(int j=0; j<13; ++j){
				for(int k=0; k<13; ++k){
					if(conv1_out[i][j][k]>0)
						conv1_out[i][j][k]=1.0;
					else if(conv1_out[i][j][k]<0)
						conv1_out[i][j][k]=-1.0;
					//printf("%Lf\n",  conv1_out[i][j][k]);

				}
			}
		}
	    for(int s=0; s<5; s++){
			for(int i=0; i<10; ++i){
				for(int j=0; j<10; ++j){
					tempo=0;
					for(int p=0; p<5; ++p){
						for(int l=0; l<3; ++l){
							for(int m=0; m<3; ++m){
								tempo+=(conv1_out[p][i+l][j+m]*conv2_weight[s][p][l][m]);

								//printf("%Lf %Lf\n",input_normalize[i+l][j+m], conv1_weight[l][m] );
							}
						}
						//printf("\n");
						
					}
					
					tempo+=conv2_bias[s];
					if(tempo > conv2_out[s][i/2][j/2])
						conv2_out[s][i/2][j/2]=tempo;
					//printf("%Lf\n",  tempo);

				}
			}
	}
		long double flatten[125];
		for(int i=0; i<5; ++i){
			for(int j=0; j<5; ++j){
				for(int k=0; k<5; ++k){
					// if(conv2_out[i][j][k]<0)
					// 	conv2_out[i][j][k]=0.0;

					flatten[i*25+j*5+k]=conv2_out[i][j][k];
					//printf("%Lf\n", flatten[i*25+j*5+k]);
				}

			}
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

	printf("Test Accuracy= %Lf\n", (long double)correct/total);
	return 0;
	//close(fd2);

}