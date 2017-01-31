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
column = N;
row = N/P;
//2D matrix are stored in Row major style 
a = (int *)calloc(column*row,sizeof(int));
x = (int *)calloc(N,sizeof(int));
c = (int *)calloc(row,sizeof(int));
buf = (int *)calloc(column,sizeof(int));
if(a==NULL||x==NULL||c==NULL||buf==NULL)
{
	if(p==0)
	printf("Error in alocating %fGB memory...Exiting\n",(float)(sizeof(int)*N*N)/(1024*1024*1024));
	MPI_Finalize();
     	exit(0);
}
for(i=0;i<row;i++)
	for(j=0;j<column;j++)
		a[i*column + j] = j+1;

if(p==0)
{
	gettimeofday(&start_tv,NULL);
}
//Initilaize values.
for(i=0;i<N;i++)
{
	x[i] = 1;
}
for(i=0;i<row;i++)
{
	c[i] = 0;
}

while(Idx>0)
{
//Calculate Partial Matrix Multiplication
	for(i=0;i<row;i++)
	{
		for(j=0;j<column;j++)
		{
			c[i] = c[i]+ x[j] * a[i*column+j];
		}
	}

//Store the local result in x
	
	for(j=0;j<row;j++)
	{
		x[p*row+j] = c[j];
	}
	
	for(j=0;j<P;j++)
	{
		if(j==p)
		{
			//Send data to everyone
			for(i=0;i<P;i++)
			{
				if(i!=p)
				{
					MPI_Send(&x[p*N/P],N/P,MPI_INT,i,0,MPI_COMM_WORLD);
				}
			}
		}
		else
		{
			//Receive data from all the other processor
			MPI_Recv(&x[j*N/P],N/P,MPI_INT,j,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
		}
			
	}
	Idx--;
	for(i=0;i<row;i++)
	{
		c[i] = 0;
	}
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
