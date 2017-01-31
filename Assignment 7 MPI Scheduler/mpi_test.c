#include<mpi.h>
#include<stdio.h>
#include<unistd.h>
int main(int argc,char *argv[])
{

int size, rank,i;
char hostname[128];
MPI_Init(&argc,&argv);

MPI_Comm_rank(MPI_COMM_WORLD, &rank);
MPI_Comm_size(MPI_COMM_WORLD, &size);
i=gethostname(hostname,sizeof hostname);
printf("In process %d\n and Hostname %s\n",rank,hostname);

MPI_Finalize();
return 0;
}
