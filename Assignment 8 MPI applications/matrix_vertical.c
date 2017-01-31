#include<mpi.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/time.h>
int main(int argc,char *argv[])
{

int P, p,i ,*a, *x, N,temp, *c,j,row, column,*buf,k,Idx=20;
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
column = N/P;
row = N;
//2D matrix are stored in Column major style in 1D matrix
a = (int *)calloc(column*row,sizeof(int));
x = (int *)calloc(column,sizeof(int));
c = (int *)calloc(N,sizeof(int));
buf = (int *)calloc(column,sizeof(int));
if(a==NULL||x==NULL||c==NULL||buf==NULL)
{
	if(p==0)
	printf("Error in alocating %fGB memory...Exiting\n",(float)(sizeof(int)*N*N)/(1024*1024*1024));
	MPI_Finalize();
     	exit(0);
}
for(i=0;i<column;i++)
	for(j=0;j<row;j++)
		a[i*row + j] = p*row+i+1;
if(p==0)
{
	gettimeofday(&start_tv,NULL);
}
//Initilaize values.
for(i=0;i<column;i++)
{
	x[i] = 1;
}
for(i=0;i<N;i++)
{
	c[i] = 0;
}

while(Idx>0)
{
//Calculate Partial Matrix Multiplication
	for(j=0;j<row;j++)
	{
		for(i=0;i<column;i++)
		{
			
			c[j] = c[j] + x[i] *a[i*row + j];
		}
		
	}


//Store the local result in x
	for(k=0;k<column;k++)
	{
		x[k] = c[p*column+k];
		
	}
	
	for(i=0;i<P;i++)
	{
		
		if(i!=p)
		{
			//Send local result to every other processor.
			MPI_Send(&c[i*N/P],N/P,MPI_INT,i,0,MPI_COMM_WORLD);
				
			}
		else
		{
			for(j=0;j<P;j++)
			{
				if(j!=p)
				{
					//Get result from all other Nodes and add it to Local result
					MPI_Recv(buf,column,MPI_INT,j,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
					for(k=0;k<column;k++)
					{
						x[k] = x[k] + buf[k];
					}
					
				}
			}
		}
		
	}
	for(k=0;k<N;k++)
	{
		c[k] = 0;
	}
	Idx--;
}

if(p==0)
{
	gettimeofday(&tv,NULL);
     	double elaspsed = (double)(tv.tv_sec - start_tv.tv_sec) + (double)(tv.tv_usec -start_tv.tv_usec)/1000000;
     	printf("%f",elaspsed);
}
MPI_Finalize();
return 0;
}
