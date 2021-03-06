#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<sys/time.h>
int main(int argc,char *argv[])
{
	int arr_size = 10,numthrds,result=0,mode=0;
	struct timeval tv;
	struct timeval start_tv;
	if(argc!=4)
	{
		printf("Few number of parameters..exiting");
		exit(0);
	}
	numthrds = atoi(argv[1]);
	arr_size = atoi(argv[2]);
	mode = atoi(argv[3]);
	int j,*ptr = (int *)calloc(arr_size,sizeof(int));
	omp_set_num_threads(numthrds);	
	
	for(j=0;j<arr_size;j++)
	{
		ptr[j] = rand()%arr_size;
	}
	result = ptr[0];
	
	
	gettimeofday(&start_tv,NULL);
	if(mode==1)
	{
		
		
		for(int i=0;i<arr_size;i++)
		{
			if(result>ptr[i])
			{
					result = ptr[i];
			}
			
		}
	}
	if(mode==2)
	{
		
		#pragma omp parallel for schedule(static) default(shared) reduction(min:result)
		for(int i=0;i<arr_size;i++)
		{
			if(result>ptr[i])
			{
					result = ptr[i];
			}
			
		}
	}
	if(mode==3)
	{
		
		#pragma omp parallel for schedule(dynamic,1) default(shared) reduction(min:result)
		for(int i=0;i<arr_size;i++)
		{
			if(result>ptr[i])
			{
					result = ptr[i];
			}
			
		}
	}
	if(mode==4)
	{
		
		#pragma omp parallel for schedule(dynamic,1000) default(shared) reduction(min:result)
		for(int i=0;i<arr_size;i++)
		{
			if(result>ptr[i])
			{
					result = ptr[i];
			}
			
		}
	}
	if(mode==5)
	{
		
		#pragma omp parallel for schedule(dynamic,1000000) default(shared) reduction(min:result)
		for(int i=0;i<arr_size;i++)
		{
			if(result>ptr[i])
			{
					result = ptr[i];
			}
			
		}
	}
	gettimeofday(&tv,NULL);
	double elaspsed = (double)(tv.tv_sec - start_tv.tv_sec) + (double)(tv.tv_usec -start_tv.tv_usec)/1000000;
	printf("%f",elaspsed);
	return 0;
}

