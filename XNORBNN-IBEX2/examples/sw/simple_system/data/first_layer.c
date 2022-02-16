#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
	FILE * fd1;
	fd1=fopen("images_array.txt",  "r");
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
	int i,j,k;
	char in[20];
	double sum[5];
	double mean[5];
	//read input;
	for(int b=0; b<1; b++){
		double out[5][26][26]={};
		double out_norm[5][26][26]={};
		char in[20];
		for(i=0; i<28; i++){
			for(j=0; j<28; j++){
				
				fgets(in, 10, fd1);
				//printf("%s\n", in);
				input[i][j]=atoi(in);
			}
		}	
		//normalize
		for(i=0; i<28; i++){
			for(j=0; j<28; j++){
				//printf("%d\n", input[i][j]);
				input_normalize[i][j]=input[i][j]/(255.0);
				
			}
		}

		//conv
		int l,m;
		
			for(i=0; i<26; i++){
				for(j=0; j<26; j++){
					for(k=0; k<5; k++){
						out[k][i][j]=0;
						for(l=0; l<3; l++){
							for(m=0; m<3; m++){
								out[k][i][j]+=(input_normalize[i+l][j+m]*filter[k][l][m]);
						}
					}
					out[k][i][j]+=bias[k];
				}
			}
		}
		
		
		
		for(k=0; k<5; k++){
			sum[k]=0;
			for(i=0; i<26; i++){
				for(j=0; j<26; j++){
					//printf("%f\n", out[k][i][j]);
					// if(out[k][i][j] > 0)
					// 	write(fd2, "1\n", 4);
					// else
					// 	write(fd2, "-1\n", 4);
					sum[k]+=out[k][i][j];
				}
			}
			mean[k]=sum[k]/676.0;
		}
		
		for(k=0; k<5; k++){
			for(i=0; i<26; i++){
				for(j=0; j<26; j++){
					//printf("%f\n", out[k][i][j]);
					// if(out[k][i][j] > 0)
					// 	write(fd2, "1\n", 4);
					// else
					// 	write(fd2, "-1\n", 4);
					printf("%lf\n", out[k][i][j]);
				}
			}
		}


	}
	fclose(fd1);
	//close(fd2);

}