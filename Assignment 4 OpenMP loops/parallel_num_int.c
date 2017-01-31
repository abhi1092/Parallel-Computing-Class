#include<omp.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
int main(int argc,char *argv[])
{
	int a,b,n,I,x,f,mode,op,j;
	int arr_size = 10,numthrds;
	int sum=0,i; 
	struct timeval tv;
	struct timeval start_tv;
	if(argc!=7)
	{
		printf("Few number of parameters..exiting");
		exit(0);
	}
	numthrds = atoi(argv[1]);
	mode = atoi(argv[2]);
	a = atoi(argv[3]);
	b = atoi(argv[4]);
	n = atoi(argv[5]);
	op = atoi(argv[6]);
	omp_set_num_threads(numthrds);
	gettimeofday(&start_tv,NULL);	
	if(mode==1)
	{
		
		for(int i=1;i<=n;i++)
		{
		x = a+(i+0.5)*(b-a)/n;
		for(j=0;j<op;j++)
		{
			f = f +  x*x;
		}
		I = I + f*(b-a)/n;	
		}
	}
	if(mode==2)
	{
		#pragma omp parallel for schedule(dynamic,1) reduction(+:I)
		for(int i=1;i<=n;i++)
		{
		//printf("In thread %d\n",omp_get_thread_num());
		x = a+(i+0.5)*(b-a)/n;
		for(j=0;j<op;j++)
		{
			f = f +  x*x;
		}
		I = I + f*(b-a)/n;
			
		}
	}
	if(mode==3)
	{
		#pragma omp parallel for schedule(dynamic,1000) reduction(+:I)
		for(int i=1;i<=n;i++)
		{
		//printf("In thread %d\n",omp_get_thread_num());
		x = a+(i+0.5)*(b-a)/n;
		for(j=0;j<op;j++)
		{
			f = f +  x*x;
		}
		I = I + f*(b-a)/n;
			
		}
	}
	gettimeofday(&tv,NULL);
	double elaspsed = (double)(tv.tv_sec - start_tv.tv_sec) + (double)(tv.tv_usec -start_tv.tv_usec)/1000000;
	printf("%f",elaspsed);
	return 0;
}
