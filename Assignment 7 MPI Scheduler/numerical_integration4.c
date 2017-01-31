#include<mpi.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/time.h>
int main(int argc,char *argv[])
{
  int size,j,p,i,P,N,a,b,op,granularity,I=0;
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
		//Master
      int send_work[2], Received_status, processor_status = P,final,work_dist = 0, total_sent_work=0;
      gettimeofday(&start_tv,NULL);
      //Start Distribution of initial work as 3 chunks to each process
      for(i=1;i<P;i++)
        {
	  for(j=0;j<3;j++)
	     {
	      send_work[0] = work_dist * granularity;
	      send_work[1] = (work_dist+1) * granularity;
	      work_dist++;
	      total_sent_work++;
	      final = send_work[1];
	      if(send_work[0]>=N)
		{
		  send_work[0] = -1;
		  send_work[1] = -1;
		  total_sent_work--;
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
	}
      MPI_Status status;
      //Send work to worker who has finished
      while(total_sent_work != 0)
        {
          MPI_Recv(&Received_status,1,MPI_INT,MPI_ANY_SOURCE,0,MPI_COMM_WORLD,&status);
		
	  total_sent_work--;
	
          I = I + Received_status;
          send_work[0] = final;
          send_work[1] = final + granularity;
          final = send_work[1];
	  total_sent_work++;
          if(send_work[0]>=N)
            {
              send_work[0] = -1;
              send_work[1] = -1;
	      total_sent_work--;
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
		//Worker
      int  x ,index[3] ,flag, f = 0, recv_buffer1[2],recv_buffer2[2],recv_buffer3[2],working_buffer[2],recv_count=3,channel[3],outcome,send_flag=0,ready_to_recv[3],Send_status,k;
	MPI_Request request[3];
	MPI_Status status[3];
	//Flag to check whether Channel is open or not
	channel[0] = 1;
	channel[1] = 1;
	channel[2] = 1;
	//Flag to check on which channel we need to send data
	ready_to_recv[0] = 1;
	ready_to_recv[1] = 1;
	ready_to_recv[2] = 1;
	while(1)
	{
		if(channel[0]==1&&ready_to_recv[0]==1)
			MPI_Irecv(recv_buffer1,2,MPI_INT,0,0,MPI_COMM_WORLD,&request[0]);
		if(channel[1]==1&&ready_to_recv[1]==1)
      		MPI_Irecv(recv_buffer2,2,MPI_INT,0,0,MPI_COMM_WORLD,&request[1]);
		if(channel[2]==1&&ready_to_recv[2]==1)
      		MPI_Irecv(recv_buffer3,2,MPI_INT,0,0,MPI_COMM_WORLD,&request[2]);
		ready_to_recv[0] = 0;
		ready_to_recv[1] = 0;
		ready_to_recv[2] = 0;
		//Check until we recive at least 1 data from all active channels
		while(1)
		{
			MPI_Waitsome(3,request,&outcome,index,status);
			if(outcome>0)
			break;
		}
		//For each channel which has recived data do work and send back to sender
		for(i=0;i<outcome;i++)
		{
			send_flag=1;
			if(index[i]==0)
			{
	 	 		working_buffer[0] = recv_buffer1[0];
	   			working_buffer[1] = recv_buffer1[1];
	   			if(working_buffer[0]==-1)
				{
					channel[0]=0;
					recv_count--;
					send_flag=0;
				}
				else
				{
					ready_to_recv[0] = 1;
				}
			}
			if(index[i]==1)
			{
	 	 		working_buffer[0] = recv_buffer2[0];
	   			working_buffer[1] = recv_buffer2[1];
	   			if(working_buffer[0]==-1)
				{
					channel[1]=0;
					recv_count--;
					send_flag=0;
				}
				else
				{
					ready_to_recv[1] = 1;
				}
			}
			if(index[i]==2)
			{
	 	 		working_buffer[0] = recv_buffer3[0];
	   			working_buffer[1] = recv_buffer3[1];
	   			if(working_buffer[0]==-1)
				{
					channel[2]=0;
					recv_count--;
					send_flag=0;
				}
				else
				{
					ready_to_recv[2] = 1;
				}
			}
			if(send_flag==1)
			{
				//Do the work and send back to master
				I = 0;
				f = 0;
				for(k=working_buffer[0];k<working_buffer[1];k++)
				{
					x = a + (k+0.5)*(b-a)/N;
					for(j=0;j<op;j++)
					{
						f = f + x*x;
					}
						I = I + f*(b-a)/N;
					}
					Send_status = I;
				MPI_Send(&Send_status,1,MPI_INT,0,0,MPI_COMM_WORLD);
				
			}
			
		}
		//Break if all 3 channels are closed.
		if(recv_count==0)
		break;
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
