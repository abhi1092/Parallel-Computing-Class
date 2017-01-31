#include<mpi.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/time.h>
int main(int argc,char *argv[])
{

  int size,j,p,i,P,N=100,a=1,b=50,Received_I,f,op=1000,x,I;
 char hostname[128];
 struct timeval tv;
 struct timeval start_tv;
 MPI_Init(&argc,&argv);
 MPI_Comm_rank(MPI_COMM_WORLD, &p);
 MPI_Comm_size(MPI_COMM_WORLD, &P);
 if(argc!=5)
   {
     printf("Few number of parameters..exiting");
     MPI_Finalize();
     exit(0);
   }
 a = atoi(argv[1]);
 b = atoi(argv[2]);
 N = atoi(argv[3]);
 op = atoi(argv[4]);
 if(p==0)
   {
     gettimeofday(&start_tv,NULL);
   }
   //All Processors willdotheir share of work
 for(i=p*N/P;i<(p+1)*N/P;i++)
  {
    x = a + (i+0.5)*(b-a)/N;
    for(j=0;j<op;j++)
      {
	f = f + x*x;
      }
    I = I + f*(b-a)/N;
  }
 if(p==0)
   { 
     for(i=P-1;i>0;i--)
       {
	 //Receive from all other processors
	 MPI_Recv(&Received_I,1,MPI_INT,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
	 I = I + Received_I;
       }
     gettimeofday(&tv,NULL);
     double elaspsed = (double)(tv.tv_sec - start_tv.tv_sec) + (double)(tv.tv_usec -start_tv.tv_usec)/1000000;
     printf("%f",elaspsed);
   }
 else
   {	
	//Everyone except 0 processor will send their work
     MPI_Send(&I,1,MPI_INT,0,0,MPI_COMM_WORLD);
   }
 MPI_Finalize();
 return 0;
}
