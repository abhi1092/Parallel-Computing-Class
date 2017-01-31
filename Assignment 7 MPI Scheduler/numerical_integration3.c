#include<mpi.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/time.h>
int main(int argc,char *argv[])
{
  int size,j,p,i,P,N,a,b,op,I=0,granularity;
  struct timeval tv;
  struct timeval start_tv;
  MPI_Init(&argc,&argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &p);
  MPI_Comm_size(MPI_COMM_WORLD, &P);
  if(argc!=6)
    {
      printf("Few number of parameters..exiting");
      MPI_Finalize();
      exit(0);
    }
  a = atoi(argv[1]);
  b = atoi(argv[2]);
  N = atoi(argv[3]);
  op = atoi(argv[4]);
  granularity = atoi(argv[5]);
  if(p==0)
    {
      int total_work_sent=0, send_work[2], Received_status,final;
      gettimeofday(&start_tv,NULL);
      //Start Distribution of initial work
      for(i=1;i<P;i++)
	{
	  send_work[0] = (i-1) * granularity;
	  send_work[1] = i * granularity;
	  final = send_work[1];
	  total_work_sent++;
	  if(send_work[0]>=N)
	    {
	      send_work[0] = -1;
	      send_work[1] = -1;
	      total_work_sent--;
	    }
	  else
	    {
	      if(send_work[1] > N)
		{
		  send_work[1] = N;
		}
	    }
	  MPI_Send(send_work,2,MPI_INT,i,0,MPI_COMM_WORLD);
	}
      MPI_Status status;
      //Send work to worker who has finished
      while(total_work_sent != 0)
	{
	  MPI_Recv(&Received_status,1,MPI_INT,MPI_ANY_SOURCE,0,MPI_COMM_WORLD,&status);
	  total_work_sent--;
	  I = I + Received_status;
	  send_work[0] = final;
	  send_work[1] = final + granularity;
	  final = send_work[1];
	  total_work_sent++;
	  if(send_work[0]>=N)
	    {
	      send_work[0] = -1;
	      send_work[1] = -1;
	      total_work_sent--;
	    }
	  else
	    {
	      if(send_work[1] > N)
			{
				send_work[1] = N;
			}
	    }
	  MPI_Send(send_work,2,MPI_INT,status.MPI_SOURCE,0,MPI_COMM_WORLD);	  
	}
    }
  else
    {
      int Received_work[2], Send_status,f,x;
      //Receive work from Master
      MPI_Recv(Received_work,2,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
      while(Received_work[1]!=-1)
		{
			I = 0;
			f = 0;
			for(i=Received_work[0];i<Received_work[1];i++)
			{
				x = a + (i+0.5)*(b-a)/N;
				for(j=0;j<op;j++)
				{
					f = f + x*x;
				}
				I = I + f*(b-a)/N;
			}
			Send_status = I;
			MPI_Send(&Send_status,1,MPI_INT,0,0,MPI_COMM_WORLD);
			//Work Done. Receieve More Work
			MPI_Recv(Received_work,2,MPI_INT,0,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
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
