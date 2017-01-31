#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/time.h>
int main(int argc,char *argv[])
{
  int j,i,P,N,a,b,op,I=0,f,x;
  struct timeval tv;
  struct timeval start_tv;
  if(argc!=5)
    {
      printf("Few number of parameters..exiting");
      exit(0);
    }
  a = atoi(argv[1]);
  b = atoi(argv[2]);
  N = atoi(argv[3]);
  op = atoi(argv[4]);
  I = 0;
  gettimeofday(&start_tv,NULL);
  for(i=0;i<N;i++)
    {
      x = a + (i+0.5)*(b-a)/N;
      f = 0;
      for(j=0;j<op;j++)
	{
	  f = f + x*x;
	}
      I = I + f*(b-a)/N;
    }
  gettimeofday(&tv,NULL);
  double elaspsed = (double)(tv.tv_sec - start_tv.tv_sec) + (double)(tv.tv_usec -start_tv.tv_usec)/1000000;
  printf("%f",elaspsed);
}

