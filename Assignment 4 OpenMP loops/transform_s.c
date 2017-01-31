#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<sys/time.h>
int main(int argc,char *argv[])
{
	int arr_size = 10,numthrds,mode=1;
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
	for(j=0;j<arr_size;j++)
	{
		ptr[j] = rand();
	}
	omp_set_num_threads(numthrds);	
	gettimeofday(&start_tv,NULL);
	if(mode==1)
	{
		for(int j=0;j<arr_size;j++)
		{
			ptr[j] = ptr[j]*ptr[j];
		}
	}
	if(mode==2)
	{
		#pragma omp parallel for default(shared) schedule(static)
		for(int j=0;j<arr_size;j++)
		{
			printf("In thread %d\n",omp_get_thread_num());
			ptr[j] = ptr[j]*ptr[j];
		}
	}
	if(mode==3)
	{
		#pragma omp parallel for default(shared) schedule(dynamic,1)
		for(int j=0;j<arr_size;j++)
		{
			printf("In thread %d\n",omp_get_thread_num());
			ptr[j] = ptr[j]*ptr[j];
		}
	}
	if(mode==4)	
	{
		#pragma omp parallel for default(shared) schedule(dynamic,1000)
		for(int j=0;j<arr_size;j++)
		{
			ptr[j] = ptr[j]*ptr[j];
		}
	}
	if(mode==5)
	{
		#pragma omp parallel for default(shared) schedule(dynamic,1000000)
		for(int j=0;j<arr_size;j++)
		{
			ptr[j] = ptr[j]*ptr[j];
		}
	}
	gettimeofday(&tv,NULL);
	double elaspsed = (double)(tv.tv_sec - start_tv.tv_sec) + (double)(tv.tv_usec -start_tv.tv_usec)/1000000;
	printf("%f",elaspsed);
	free(ptr);
	return 0;
}
