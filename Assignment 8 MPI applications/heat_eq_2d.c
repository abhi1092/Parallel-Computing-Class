#include<mpi.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/time.h>
int main(int argc,char *argv[])
{
	int P, p,i, *h_k, *h_k_1,*temp,N,j,*buf1, *buf2,H=20,h1,h2,h3,h4,h5,h6,h7,h8,h9;
	struct timeval tv;
 	struct timeval start_tv;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &p);
	MPI_Comm_size(MPI_COMM_WORLD, &P);
	if(argc!=2)
	{
		if(p==0)
		printf("Few number of parameters..exiting\n");
    	 	MPI_Finalize();
     		exit(0);
	}
	N = atoi(argv[1]);
	if(P>N||N%P!=0)
	{
		if(p==0)
		printf("Wrong Size of array N and P should be multiples and N>P..Exiting\n");
		MPI_Finalize();
     		exit(0);
	}
	int column = N/P;
	int row = N;
	h_k = (int *)calloc(column*row,sizeof(int));
	h_k_1 = (int *)calloc(N*N,sizeof(int));
	buf1 = (int *)calloc(N,sizeof(int));
	buf2 = (int *)calloc(N,sizeof(int));
	if(h_k==NULL||h_k_1==NULL||buf1==NULL||buf2==NULL)
	{
		if(p==0)
		printf("Error in allocating memory..Exiting\n");
		MPI_Finalize();
		exit(0);
	}
	for(i=0;i<column;i++)
	{
		for(j=0;j<row;j++)
		{
			h_k_1[i*row + j] = 1;
		}
		
	}
	if(p==0)
   	{
     		gettimeofday(&start_tv,NULL);
   	}
	//Send Column data
	
	while(H>0)
	{
		if(p==0)
		{
			//For 0th processor only send column to right side
			for(i=0;i<column;i++);
			i--;
			MPI_Send(&h_k_1[i*N],N,MPI_INT,p+1,0,MPI_COMM_WORLD);
			MPI_Recv(&buf1[0],N,MPI_INT,p+1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			/*
			for(j=0;j<N;j++)
				{
					printf("%d ",buf1[j]);
				}
			*/
			//Compute H_k
			for(i=0;i<column;i++)
			{
				for(j=0;j<row;j++)
				{
					if((i==0&&j==0)||(i==0)||(j==0))
						h1 = h_k_1[i*row + j];
					else
						h1 = h_k_1[(i-1)*row + (j-1)];
					if(i==0)
						h2 = h_k_1[i*row + j];
					else
						h2 = h_k_1[(i-1)*row + j];
					if((i==0&&j==row-1)||(i==0)||(j==row-1))
						h3 = h_k_1[i*row + j];
					else
						h3 = h_k_1[(i-1)*row + (j+1)];
					if(j==0)
						h4 = h_k_1[i*row + j];
					else
						h4 = h_k_1[i*row + (j-1)];
					if((i==column-1&&j==0)||(i==column-1)||(j==0))
						h5 = h_k_1[i*row + j];
					else
						h5 = h_k_1[(i+1)*row + (j-1)];
					if(i==column-1)
						h6 = buf1[j];
					else
						h6 = h_k_1[(i+1)*row + j];
					if(i==column-1&&j==row-1||(i==column-1)||(j==row-1))
						h7 = h_k_1[i*row + j];
					else
						h7 = h_k_1[(i+1)*row + (j+1)];
					if(j==row-1)
						h8 = h_k_1[i*row + j];
					else
						h8 = h_k_1[(i)*row + (j+1)];
					h9 = h_k_1[i*row + j];
					h_k[i*row + j] = (h1 + h2 + h3 + h4 + h5 + h6 + h7 + h8 + h9)/9;
					//printf("%d %d %d %d %d %d %d %d i=%d j=%d\n",h1,h2,h3,h4,h5,h6,h7,h8,i,j);
				}
			}
		}
		else
		{
			if(p==P-1)
			{
				//Last processor will send data to left and also receive from left
				if(p%2==0)
				{
					MPI_Send(&h_k_1[0],N,MPI_INT,p-1,0,MPI_COMM_WORLD);
					MPI_Recv(&buf1[0],N,MPI_INT,p-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
				}
				else
				{
					MPI_Recv(&buf1[0],N,MPI_INT,p-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
					MPI_Send(&h_k_1[0],N,MPI_INT,p-1,0,MPI_COMM_WORLD);
				}
				/*
				for(j=0;j<N;j++)
				{
					printf("%d ",buf1[j]);
				}
				*/
				for(i=0;i<column;i++)
				{
					for(j=0;j<row;j++)
					{
						if((i==0&&j==0)||(i==0)||(j==0))
							h1 = buf1[j];
						else
							h1 = h_k_1[(i-1)*row + (j-1)];
						if(i==0)
							h2 = buf1[j];
						else
							h2 = h_k_1[(i-1)*row + j];
						if((i==0&&j==row-1)||(i==0)||(j==row-1))
							h3 = h_k_1[i*row + j];
						else
							h3 = h_k_1[(i-1)*row + (j+1)];
						if(j==0)
							h4 = h_k_1[i*row + j];
						else
							h4 = h_k_1[i*row + (j-1)];
						if((i==column-1&&j==0)||(i==column-1)||(j==0))
							h5 = h_k_1[i*row + j];
						else
							h5 = h_k_1[(i+1)*row + (j-1)];
						if(i==column-1)
							h6 = h_k_1[i*row + j];
						else
							h6 = h_k_1[(i+1)*row + j];
						if(i==column-1&&j==row-1||(i==column-1)||(j==row-1))
							h7 = h_k_1[i*row + j];
						else
							h7 = h_k_1[(i+1)*row + (j+1)];
						if(j==row-1)
							h8 = h_k_1[i*row + j];
						else
							h8 = h_k_1[(i)*row + (j+1)];
							h9 = h_k_1[i*row + j];
						h_k[i*row + j] = (h1 + h2 + h3 + h4 + h5 + h6 + h7 + h8 + h9)/9;
						//printf("%d %d %d %d %d %d %d %d\n",h1,h2,h3,h4,h5,h6,h7,h8);
					}	
				}
			}
			else
			{
				if(p%2!=0)
				{
					MPI_Recv(&buf1[0],N,MPI_INT,p-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
					MPI_Recv(&buf2[0],N,MPI_INT,p+1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
					MPI_Send(&h_k_1[0],N,MPI_INT,p-1,0,MPI_COMM_WORLD);
					for(i=0;i<column;i++);
					i--;
					MPI_Send(&h_k_1[i*N],N,MPI_INT,p+1,0,MPI_COMM_WORLD);
				}
				else
				{
					MPI_Send(&h_k_1[0],N,MPI_INT,p-1,0,MPI_COMM_WORLD);
					for(i=0;i<column;i++);
					i--;
					MPI_Send(&h_k_1[i*N],N,MPI_INT,p+1,0,MPI_COMM_WORLD);
					MPI_Recv(&buf1[0],N,MPI_INT,p-1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
					MPI_Recv(&buf2[0],N,MPI_INT,p+1,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
				}
				
				
				/*for(j=0;j<N;j++)
				{
					printf("%d ",buf1[j]);
				}	
				for(j=0;j<N;j++)
				{
					printf("%d ",buf2[j]);
				}
				*/
				for(i=0;i<column;i++)
				{
					for(j=0;j<row;j++)
					{
						if((i==0&&j==0)||(i==0)||(j==0))
							h1 = h_k_1[i*row + j];
						else
							h1 = h_k_1[(i-1)*row + (j-1)];
						if(i==0)
							h2 = buf1[j];
						else
							h2 = h_k_1[(i-1)*row + j];
						if((i==0&&j==row-1)||(i==0)||(j==row-1))
							h3 = h_k_1[i*row + j];
						else
							h3 = h_k_1[(i-1)*row + (j+1)];
						if(j==0)
							h4 = h_k_1[i*row + j];
						else
							h4 = h_k_1[i*row + (j-1)];
						if((i==column-1&&j==0)||(i==column-1)||(j==0))
							h5 = h_k_1[i*row + j];
						else
							h5 = h_k_1[(i+1)*row + (j-1)];
						if(i==column-1)
							h6 = buf2[j];
						else
							h6 = h_k_1[(i+1)*row + j];
						if(i==column-1&&j==row-1||(i==column-1)||(j==row-1))
							h7 = h_k_1[i*row + j];
						else
							h7 = h_k_1[(i+1)*row + (j+1)];
						if(j==row-1)
							h8 = h_k_1[i*row + j];
						else
							h8 = h_k_1[(i)*row + (j+1)];
						h9 = h_k_1[i*row + j];
						h_k[i*row + j] = (h1 + h2 + h3 + h4 + h5 + h6 + h7 + h8 + h9)/9;
						//printf("%d %d %d %d %d %d %d %d\n",h1,h2,h3,h4,h5,h6,h7,h8);
					}
				}
			}
		}
		H--;
		temp = h_k_1;
		h_k_1 = h_k;
		h_k = temp;
	}
	/*for(i=0;i<column;i++)
	{
		for(j=0;j<row;j++)
		{
			//printf("%d ",h_k[i*N+j]);
		}
	}
	//printf("\n");*/
	if(p==0)
	{
		 gettimeofday(&tv,NULL);
     		double elaspsed = (double)(tv.tv_sec - start_tv.tv_sec) + (double)(tv.tv_usec -start_tv.tv_usec)/1000000;
     		printf("%f",elaspsed);
	}
	MPI_Finalize();
	return 0;
}
