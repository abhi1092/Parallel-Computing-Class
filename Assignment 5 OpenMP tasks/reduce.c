#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<time.h>
#include<sys/time.h>
int granularity;
int schedule;
int reduce(int*,int,int);
int reduce_sequential(int *a,int n);
int main(int argc,char *argv[])
{
	int *a,b,i,n=10,numthrds,option;
	struct timeval tv;
	struct timeval start_tv;
	//srand(time(NULL));
	if(argc!=6)
	{
		printf("Few number of parameters..exiting");
		exit(0);
	}
	numthrds = atoi(argv[1]);
	n = atoi(argv[2]);
	option = atoi(argv[3]);
	granularity = atoi(argv[4]);
	schedule = atoi(argv[5]);
	a = (int *)calloc(n,sizeof(int));
	if(a==NULL)
	{
		printf("Failed memory allocation");
		exit(0);
	}
	for(i=0;i<n;i++)
	a[i] = rand()%n;
	omp_set_dynamic(0);
	omp_set_num_threads(numthrds);
	gettimeofday(&start_tv,NULL);
	if(option==1)
	{
		//In sequential
		b = reduce_sequential(a,n);
	}
	else
	{
		//Parallel Execution
		#pragma omp parallel
		{
			#pragma omp single
			b = reduce(a,0,n);

		}
	}
	gettimeofday(&tv,NULL);
	double elaspsed = (double)(tv.tv_sec - start_tv.tv_sec) + (double)(tv.tv_usec -start_tv.tv_usec)/1000000;
	printf("%f\n",elaspsed);
	return 0;

}


int reduce(int* a, int start, int end)
{
	int i,b,c,found;
	if(end-start<=granularity)
	{
		found = a[start];
		if(schedule==1)
		{
			#pragma omp parallel for schedule(static) default(shared) reduction(min:found)
			for(int i=start;i<end;i++)
			{
				if(found>a[i])
				{
						found = a[i];
				}
			
			}
			return found;
		}
		if(schedule==2)
		{
			#pragma omp parallel for schedule(dynamic,1) default(shared) reduction(min:found)
			for(int i=start;i<end;i++)
			{
				if(found>a[i])
				{
						found = a[i];
				}
			
			}
			return found;
		}
		if(schedule==3)
		{
			#pragma omp parallel for schedule(dynamic,1000) default(shared) reduction(min:found)
			for(int i=start;i<end;i++)
			{
				if(found>a[i])
				{
						found = a[i];
				}
			
			}
			return found;
		}
		
	}

		#pragma omp task shared(b)
		b = reduce(a,start,(end+start)/2);
		#pragma omp task shared(c)
		c = reduce(a,(end+start)/2,end);
		#pragma omp taskwait
		if(c>b)
		return b;
		else
		return c;
	
	

}

int reduce_sequential(int *a,int n)
{
	int result, i;
	result = a[0];
	for(i=0;i<n;i++)
		{
			if(result>a[i])
			{
					result = a[i];
			}
			
		}
	return result;
}
