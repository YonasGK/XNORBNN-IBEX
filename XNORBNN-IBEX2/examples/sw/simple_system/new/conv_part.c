#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
	FILE * fd1, *fd2, *fd3, *fd4;
	fd1=fopen("images_array.txt",  "r");
	fd2=fopen("weight.txt", "r");
	fd3=fopen("labels_array.txt", "r");
	fd4=fopen("dense2.txt", "r");

	//int fd2=open("../data/out_conv1.txt", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
	int input[28][28];
	 long double input_normalize[28][28];
	 long double conv1_weight[5][5]; 

	 long double conv_bias[4]={0.0591880, -0.08844928, -0.0369215, -0.16546902};
	
	 long double conv2_weight[5][5];
	
	
	 long double conv3_weight[5][5];
	
	 long double conv4_weight[5][5];
	 long double dense1_weight[144][20];
	 long double dense1_bias[20]={-0.09032427,0.006174218,0.42395836,-0.0013010155,-0.008038027,0.28216454,-0.005602987
,0.1493831,0.29705054,-0.46581152,0.108662196,-0.44596985,0.19509909,0.01383665,-0.07060398,0.3249583,0.19703422
,-0.024708318,0.09659515,-0.2796926
};
	 long double dense2_weight[20][10];
	 long double dense2_bias[10]={-0.036719948
,0.3638167
,-0.27800068
,-0.12390471
,0.061590552
,0.33783206
,-0.097728275
,0.22064686
,-0.5143274
,0.1268391
};
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
		for(int j=0; j<5; ++j){
			
					fgets(weight_ch, 20, fd2);
					sscanf(weight_ch, "%Lf", &temp1);
					conv1_weight[i][j]=temp1;
					
					//printf("%Lf\n", temp1 );
		}
		
	}
	//get weight 2
	//printf("second layer\n");
	for(int i=0; i<5; ++i){
		for(int j=0; j<5; ++j){
			
					fgets(weight_ch, 20, fd2);
					sscanf(weight_ch, "%Lf", &temp1);
					conv2_weight[i][j]=temp1;

					//printf("%Lf\n", temp1 );
		}
		
	}
	//get weight 3
	for(int i=0; i<5; ++i){
		for(int j=0; j<5; ++j){
			
					fgets(weight_ch, 20, fd2);
					sscanf(weight_ch, "%Lf", &temp1);
					conv3_weight[i][j]=temp1;
		}
		
	}
	for(int i=0; i<5; ++i){
		for(int j=0; j<5; ++j){
			
					fgets(weight_ch, 20, fd2);
					sscanf(weight_ch, "%Lf", &temp1);
					conv4_weight[i][j]=temp1;
		}
		
	}
	for(int i=0; i<20; ++i){
		for(int j=0; j<144; ++j){
			
					fgets(weight_ch, 20, fd2);
					sscanf(weight_ch, "%Lf", &temp1);
					dense1_weight[j][i]=temp1;
		}
		
	}
	for(int i=0; i<10; ++i){
		for(int j=0; j<20; ++j){
			
					fgets(weight_ch, 20, fd2);
					sscanf(weight_ch, "%Lf", &temp1);
					dense2_weight[j][i]=temp1;
					//printf("%Lf\n", dense2_weight[j][i]);
		}
		
	}


	//read input;
	int correct=0;
	int total=20;
	for(int b=0; b<total; ++b){
		
		 long double conv1_out[24][24]={};
		 long double conv2_out[20][20]={};
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
		for(int i=0; i<28; ++i){  
			for(int j=0; j<28; ++j){
				
				input_normalize[i][j]=input[i][j]/(255.0);
				//printf("%Lf  ", input_normalize[i][j]);
				
			}
			//printf("\n");
		}


		//conv1
		
		
		for(int i=0; i<24; ++i){
			for(int j=0; j<24; ++j){
				conv1_out[i][j]=0;		
				for(int l=0; l<5; ++l){
					for(int m=0; m<5; ++m){
						conv1_out[i][j]+=(input_normalize[i+l][j+m]*conv1_weight[l][m]);
						//printf("%Lf %Lf\n",input_normalize[i+l][j+m], conv1_weight[l][m] );
					}
				}
				//printf("\n");
				conv1_out[i][j]+=conv_bias[0];
				
			}
		}

		for(int j=0; j<24; ++j){
			for(int k=0; k<24; ++k){
				if(conv1_out[j][k]<0)
					conv1_out[j][k]=0.0;
			}
		}




		//conv2
		for(int i=0; i<20; ++i){
			for(int j=0; j<20; ++j){
				conv2_out[i][j]=0;			
				for(int l=0; l<5; ++l){
					for(int m=0; m<5; ++m){
						conv2_out[i][j]+=(conv1_out[i+l][j+m]*conv2_weight[l][m]);
					}
				}
				conv2_out[i][j]+=conv_bias[1];
				
			}
		}

		for(int j=0; j<20; ++j){
			for(int k=0; k<20; ++k){
				if(conv2_out[j][k]<0)
					conv2_out[j][k]=0.0;
			}
		}
		//conv3
		for(int i=0; i<16; ++i){
			for(int j=0; j<16; ++j){
				conv3_out[i][j]=0;			
				for(int l=0; l<5; ++l){
					for(int m=0; m<5; ++m){
						conv3_out[i][j]+=(conv2_out[i+l][j+m]*conv3_weight[l][m]);
					}
				}
				conv3_out[i][j]+=conv_bias[2];
				
			}
		}

		for(int j=0; j<16; ++j){
			for(int k=0; k<16; ++k){
				if(conv3_out[j][k]<0)
					conv3_out[j][k]=0.0;
			}
		}

		//conv4
		for(int i=0; i<12; ++i){
			for(int j=0; j<12; ++j){
				conv4_out[i][j]=0;			
				for(int l=0; l<5; ++l){
					for(int m=0; m<5; ++m){
						conv4_out[i][j]+=(conv3_out[i+l][j+m]*conv4_weight[l][m]);
					}
				}
				conv4_out[i][j]+=conv_bias[3];
				
			}
		}

		for(int j=0; j<12; ++j){
			for(int k=0; k<12; ++k){
				if(conv4_out[j][k]<0)
					conv4_out[j][k]=0.0;
			}
		}
		 long double flatten[144];
		for(int i=0; i<144; ++i){
			flatten[i]=conv4_out[i%12][i/12];
			//printf("%Lf \n", flatten[i]);
		}

	 long double layer1_out[20];
  	 long double out[10];
  	 long double out_n[10];


	//compute first layer
	for(int i=0; i<20; ++i){
		layer1_out[i]=0;
		for(int j=0; j<144; ++j){
			layer1_out[i]+=(flatten[j]*dense1_weight[j][i]);
		}
		layer1_out[i]+=dense1_bias[i];
	}
	for(int i=0; i<20; ++i){
		if(layer1_out[i]<0)
			layer1_out[i]=0.0;
		//printf("%Lf\n", layer1_out[i]);
	}
	 long double sum_d1=0;
	//compute second layer
	 long double exp_sum=0.0;
	for(int i=0; i<10; ++i){
		out[i]=0;
		for(int j=0; j<20; ++j){
			out[i]+=(layer1_out[j]*dense2_weight[j][i]);
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

		fgets(label, 3, fd3);
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
	printf("%Lf\n", (long double)correct/total);
	return 0;
	//close(fd2);

}