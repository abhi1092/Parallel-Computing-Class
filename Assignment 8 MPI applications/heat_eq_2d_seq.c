#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/time.h>
int main(int argc,char *argv[])
{
	int i, *h_k, *h_k_1,N,j, H=20,h1,h2,h3,h4,h5,h6,h7,h8,h9,*temp;
	struct timeval tv;
 	struct timeval start_tv;
	if(argc!=2)
	{

		printf("Few number of parameters..exiting\n");
     		exit(0);
	}
	N = atoi(argv[1]);
	h_k = (int *)calloc(N*N,sizeof(int));
	h_k_1 = (int *)calloc(N*N,sizeof(int));
	gettimeofday(&start_tv,NULL);
	while(H>0)
	{
		for(i=0;i<N;i++)
		{
			for(j=0;j<N;j++)
			{
				if((i==0&&j==0)||(i==0)||(j==0))
						h1 = h_k_1[i*N + j];
					else
						h1 = h_k_1[(i-1)*N + (j-1)];
					if(i==0)
						h2 = h_k_1[i*N + j];
					else
						h2 = h_k_1[(i-1)*N + j];
					if((i==0&&j==N-1)||(i==0)||(j==N-1))
						h3 = h_k_1[i*N + j];
					else
						h3 = h_k_1[(i-1)*N + (j+1)];
					if(j==0)
						h4 = h_k_1[i*N + j];
					else
						h4 = h_k_1[i*N + (j-1)];
					if((i==N-1&&j==0)||(i==N-1)||(j==0))
						h5 = h_k_1[i*N + j];
					else
						h5 = h_k_1[(i+1)*N + (j-1)];
					if(i==N-1)
						h6 = h_k_1[i*N + j];
					else
						h6 = h_k_1[(i+1)*N + j];
					if(i==N-1&&j==N-1||(i==N-1)||(j==N-1))
						h7 = h_k_1[i*N + j];
					else
						h7 = h_k_1[(i+1)*N + (j+1)];
					if(j==N-1)
						h8 = h_k_1[i*N + j];
					else
						h8 = h_k_1[(i)*N + (j+1)];
					h9 = h_k_1[i*N + j];
					h_k[i*N + j] = (h1 + h2 + h3 + h4 + h5 + h6 + h7 + h8 + h9)/9;
			}
		}
		H--;
		temp = h_k_1;
		h_k_1 = h_k;
		h_k = temp;
	}

	gettimeofday(&tv,NULL);
     	double elaspsed = (double)(tv.tv_sec - start_tv.tv_sec) + (double)(tv.tv_usec -start_tv.tv_usec)/1000000;
     	printf("%f",elaspsed);
	return 0;
}
