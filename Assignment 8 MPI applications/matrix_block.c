#include<mpi.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/time.h>
#include<math.h>
int main(int argc,char *argv[])
{

int  P,p,i ,*a, *x, N,temp, *c,j,row, column,*buf,k,Idx=20,leader=0,p_row,p_column;
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
if(P>N||N%(int)sqrt(P)!=0)
{
	if(p==0)
	printf("Wrong Size of array N and P should be multiples and N>P..Exiting\n");
	MPI_Finalize();
     	exit(0);
}
column = N/sqrt(P);
row = N/sqrt(P);
p_row = p/sqrt(P);
p_column = p%(int)sqrt(P);

//2D matrix are stored in Row major style 
a = (int *)calloc(column*row,sizeof(int));
x = (int *)calloc(N/sqrt(P),sizeof(int));
c = (int *)calloc(N/sqrt(P),sizeof(int));
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
		a[i*column + j] = 1;

for(i=0;i<column;i++)
{
	x[i] = 1;
}
for(i=0;i<column;i++)
{
	c[i] = 0;
}
if(p==0)
{
	gettimeofday(&start_tv,NULL);
}
//Leader is the first process in each row.
leader = p/sqrt(P);
leader = leader * sqrt(P);

while(Idx>0)
{
	//Calucate local result of matrix multiplication 
	for(j=0;j<row;j++)
	{
		for(i=0;i<column;i++)
		{	
			c[j] = c[j] + x[i] *a[i*column + j];
		}
	}
	for(i=0;i<N/sqrt(P);i++)
	{
		x[i] = c[i];
	}
	
	//Every processor wll send data to the first process in row of the grid of process
	if(p!=leader)
	{
		MPI_Send(&x[0],N/sqrt(P),MPI_INT,leader,0,MPI_COMM_WORLD);
		//Receive aggregated data back from first processor of row , where row is equal to column of current process
		MPI_Recv(&x[0],N/sqrt(P),MPI_INT,p_column*sqrt(P),0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	}
	else
	{
		//Receive data from all processor in current row in to first process
		for(i=p+1;i<p+sqrt(P);i++)
		{
			MPI_Recv(&c[0],N/sqrt(P),MPI_INT,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
			for(j=0;j<N/sqrt(P);j++)
			{
				x[j] = x[j] + c[j];
			}
		}
		//Send the final calculated data back to processors of column = p_row. i.e First process of row i will send data to every process in column i
		for(i=0;i<sqrt(P);i++)
		{
			if(i!=p)
			{
				MPI_Send(&x[0],N/sqrt(P),MPI_INT,i*sqrt(P)+p_row,0,MPI_COMM_WORLD);
			}
		}
	}
	for(i=0;i<N/sqrt(P);i++)
	{
		c[i] = 0;
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
