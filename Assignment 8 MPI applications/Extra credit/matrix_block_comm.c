#include<mpi.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/time.h>
#include<math.h>
int main(int argc,char *argv[])
{

int  P,p,i ,*a, *x, N=3,temp, *c,j,row, column,*buf,k,Idx=20,leader=0,p_row,p_column,row_rank,row_size,leader_rank=-1,leader_size=-1,color;
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
x = (int *)calloc(N,sizeof(int));
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
//Leader is the rank of process which is first in each row. The rank is according to MPI_COMM_WORLD communicator
leader = p/sqrt(P);
leader = leader * sqrt(P);
//Process are divided in grid. Create row communicator which groups process together which belong to same row.
MPI_Comm row_com;
MPI_Comm_split(MPI_COMM_WORLD,p_row,p,&row_com);
MPI_Comm_rank(row_com, &row_rank);
MPI_Comm_size(row_com, &row_size);
//All process which are not first in row are to be excluded from the communicator
if(p==leader)
	color=1;
else
	color = MPI_UNDEFINED;
//Create Communicator for only process which are first in row in the grid of process
MPI_Comm leader_com;
MPI_Comm_split(MPI_COMM_WORLD,color,p,&leader_com);
if(p==leader)
{
	MPI_Comm_rank(leader_com, &leader_rank);
	MPI_Comm_size(leader_com, &leader_size);
}

while(Idx>0)
{
	//Compute local matrix multiplication at every process
	for(j=0;j<row;j++)
	{
		for(i=0;i<column;i++)
		{	
			c[j] = c[j] + x[i] *a[i*column + j];
		}
	}
	//Copy the result in x which is to be send
	for(i=0;i<N/sqrt(P);i++)
	{
		x[i] = c[i];
	}
	//All the locally calculated result will be aggreagted in first node of each row
	MPI_Reduce(&x[0],&c[0],N/sqrt(P),MPI_INT,MPI_SUM,0,row_com);
	
	//Each first node in row will sedn data to process 0  which will gather the data
	if(color!=MPI_UNDEFINED)
	{
		MPI_Gather(&c[0],row,MPI_INT,&x[0],row,MPI_INT,0,leader_com);
	}
	//Root Node will brocast the final x to each process
	MPI_Bcast(&x[0],N,MPI_INT,0,MPI_COMM_WORLD);

	
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

