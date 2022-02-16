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
	fd2=fopen("conv2.txt", "r");
	fd3=fopen("conv3.txt", "r");
	fd4=fopen("conv4.txt", "r");
	//int fd2=open("../data/out_conv1.txt", O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR);
	int input[28][28];
	double input_normalize[28][28];
	double filter[5][3][3]={{0.2780206, 0.35366255, 0.29091433, 0.27395338, 0.69247663, 0.6161582, 0.04120083, 0.5825324, 0.46672326
},{0.04624219, 0.4753383, 0.00691662, 0.14949693, 0.38339913, -0.0577025, -0.14632815, -0.45641762, 0.12797196
},{0.18554762,0.26278636, 0.17638539,-0.22486965, 0.12174261, 0.30587077, -0.5572523, 0.34219295, 0.24043083
},{0.12071261, -0.30822286, -0.41505295, -0.22276954, 0.44661197, 0.41622615, 0.01321389, -0.07920846, 0.30065852
}, {0.5269839, 0.1270144, -0.20268057, 0.37792975, 0.32600248, -0.19047338, 0.3118687, 0.14592902, 0.42475757
}};  

	double bias[5]={0.00618329, -0.00194861,  0.05448081, -0.00139251, -0.00672673};
	
	double conv2_weight[5][5][3][3];
	double conv2_bias[5]={-0.03368696, -0.03909106,  0.00042667, -0.02103042, -0.10698418};
	
	double conv3_weight[10][5][3][3];
	double conv3_bias[10]={-0.07137413,  0.00430224, -0.02359463,  0.08200609, -0.02242083,  0.01919815
  ,0.1166801 ,  0.14260384, -0.01440275,  0.04188612};
	
	double conv4_bias[10]={-0.03262258, -0.07641038, -0.12688339, -0.06153007, -0.0066507,   0.02872616,
  0.02134964,  0.10533614,  0.08240878, -0.00644752};
	double conv4_weight[10][10][3][3];
	double conv4_out[10][4][4];
	int i,j,k;
	char in[20];
	double sum[5];
	double mean[5];

	char weight_ch[20];
	
	double temp1;
	//get weight 2


	for(int i=0; i<5; i++){
		for(int k=0; k<3; k++){
			for(int l=0;  l<3; l++){
				for(int j=0; j<5; j++){
					fgets(weight_ch, 20, fd2);
					sscanf(weight_ch, "%lf", &temp1);
					conv2_weight[i][j][k][l]=temp1;
				}
			}
		}
		
	}
	//get weight 3
	for(int i=0; i<10; i++){
		for(int k=0; k<3; k++){
			for(int l=0;  l<3; l++){
				for(int j=0; j<5; j++){
					fgets(weight_ch, 15, fd3);
					sscanf(weight_ch, "%lf", &temp1);
					conv3_weight[i][j][k][l]=temp1;
				}
			}
		}
		
	}
	//get weight 4
	for(int i=0; i<10; i++){
		for(int k=0; k<3; k++){
			for(int l=0;  l<3; l++){
				for(int j=0; j<10; j++){
					fgets(weight_ch, 15, fd4);
					sscanf(weight_ch, "%lf", &temp1);
					conv4_weight[i][j][k][l]=temp1;
				}
			}
		}
		
	}



	//read input;
	for(int b=0; b<10; b++){
		double out[5][26][26]={};
		double conv1_out[5][26][26]={};
		double conv2_out[5][12][12]={};
		double conv3_out[10][10][10]={};
		double conv4_out[10][4][4]={};
		double out_norm[5][26][26]={};
		char in[20];

		for(int i=0; i<28; i++){
			for(int j=0; j<28; j++){
				
				fgets(in, 10, fd1);
				//printf("%s\n", in);
				input[i][j]=atoi(in);
			}
		}	
		//normalize
		for(int i=0; i<28; i++){
			for(int j=0; j<28; j++){
				//printf("%d\n", input[i][j]);
				input_normalize[i][j]=input[i][j]/(255.0);
				
			}
		}


		//conv1
		
		
			for(int i=0; i<26; i++){
				for(int j=0; j<26; j++){
					for(int k=0; k<5; k++){
						
						for(int l=0; l<3; l++){
							for(int m=0; m<3; m++){
								conv1_out[k][i][j]+=(input_normalize[i+l][j+m]*filter[k][l][m]);
						}
					}
					conv1_out[k][i][j]+=bias[k];
				}
			}
		}

		for(int i=0; i<5; i++){
			for(int j=0; j<26; j++){
				for(int k=0; k<26; k++){
					if(conv1_out[i][j][k]<0)
						conv1_out[i][j][k]=0;
				}
			}
		}
		double average1[5];
		double sum1;
		for(int i=0; i<5; i++){
			sum1=0;
			for(int j=0; j<26; j++){
				for(int k=0; k<26; k++){
					sum1+=conv1_out[i][j][k];
				}
			}
			average1[i]=sum1/676.0;
		}
		for(int i=0; i<5; i++){
			for(int j=0; j<26; j++){
				for(int k=0; k<26; k++){
					
						conv1_out[i][j][k]-=average1[i];
				}
			}
		}



		//conv2
		double temp_c2;
		for(int z=0; z<10; z++){
			for(int i=0; i<24; i++){
				for(int j=0; j<24; j++){
					temp_c2=0.0;
					for(int k=0; k<5; k++){
						
						for(int l=0; l<3; l++){
							for(int m=0; m<3; m++){
								temp_c2+=(conv1_out[k][i+l][j+m]*conv2_weight[z][k][l][m]);
						}
					}
					
			}
			temp_c2+=conv2_bias[z];
			if(conv2_out[z][i/2][j/2] < temp_c2 && temp_c2 > 0)
				conv2_out[z][i/2][j/2]=temp_c2;

		}		
				
	}
}
		double average2[10];
		double sum2;
		for(int i=0; i<10; i++){
			sum2=0;
			for(int j=0; j<12; j++){
				for(int k=0; k<12; k++){
					sum2+=conv2_out[i][j][k];
				}
			}
			average2[i]=sum2/144.0;
		}
		for(int i=0; i<10; i++){
			for(int j=0; j<12; j++){
				for(int k=0; k<12; k++){
					
						conv2_out[i][j][k]-=average2[i];
				}
			}
		}
		//conv3
		double temp_c3;
		for(int z=0; z<10; z++){
			for(int i=0; i<10; i++){
				for(int j=0; j<10; j++){
					temp_c3=0.0;
					for(int k=0; k<5; k++){
						for(int l=0; l<3; l++){
							for(int m=0; m<3; m++){
								temp_c3+=(conv2_out[k][i+l][j+m]*conv3_weight[z][k][l][m]);
						}
					}
					
			}
		}
		temp_c3+=conv3_bias[z];
		conv3_out[z][i][j]=temp_c3;		
				
	}
}

		for(int i=0; i<10; i++){
			for(int j=0; j<10; j++){
				for(int k=0; k<10 ; k++){
					if(conv3_out[i][j][k]<0)
						conv3_out[i][j][k]=0;
				}
			}
		}

		double average3[10];
		double sum3;
		for(int i=0; i<10; i++){
			sum3=0;
			for(int j=0; j<10; j++){
				for(int k=0; k<10; k++){
					sum3+=conv3_out[i][j][k];
				}
			}
			average3[i]=sum3/100.0;
		}
		for(int i=0; i<10; i++){
			for(int j=0; j<10; j++){
				for(int k=0; k<10; k++){
					
						conv3_out[i][j][k]-=average3[i];
				}
			}
		}

		//conv4
		double temp_c4;
		for(int z=0; z<10; z++){
			for(int i=0; i<8; i++){
				for(int j=0; j<8; j++){
					temp_c4=0.0;
					for(int k=0; k<10; k++){
						for(int l=0; l<3; l++){
							for(int m=0; m<3; m++){
								temp_c4+=(conv3_out[k][i+l][j+m]*conv4_weight[z][k][l][m]);
						}
					}
					
			}
			temp_c4+=conv4_bias[z];
			if(conv4_out[z][i/2][j/2] < temp_c4 && temp_c4 > 0)
				conv4_out[z][i/2][j/2]=temp_c4;
			
		}		
				
	}
}

		double average4;
		double sum4=0;
		for(int i=0; i<10; i++){
			
			for(int j=0; j<4; j++){
				for(int k=0; k<4; k++){
					sum4+=conv4_out[i][j][k];
				}
			}	
		}

		average4=sum4/160.0;
		for(int i=0; i<10; i++){
			for(int j=0; j<4; j++){
				for(int k=0; k<4; k++){
					
						conv4_out[i][j][k]-=average4;
				}
			}
		}

		for(int i=0; i<10; i++){
			for(int j=0; j<4; j++){
				for(int k=0; k<4; k++){
					printf("%lf\n", conv4_out[i][j][k]);
				}
			}
		}
		
	}
	fclose(fd1);
	fclose(fd2);
	fclose(fd4);
	fclose(fd3);
	return 0;
	//close(fd2);

}