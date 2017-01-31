#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<time.h>
#include<sys/time.h>
int granularity;
int find_first(int *a,int target,int start,int end);
int search(int *a,int start, int end,int n,int target);
int find_first_sequential(int *a,int target,int n);
int main(int argc,char *argv[])
{
	int *a,target,numthrds,n,i,b=-1,option;
	struct timeval tv;
	struct timeval start_tv;
	//srand(time(NULL));
	if(argc!=5)
	{
		printf("Few number of parameters..exiting");
		exit(0);
	}
	numthrds = atoi(argv[1]);
	n = atoi(argv[2]);
	option = atoi(argv[3]);
	granularity = atoi(argv[4]);
	target = rand()%n;
	a = (int *)calloc(n,sizeof(int));
	if(a==NULL)
	{
		printf("Failed memory allocation.");
		exit(0);
	}	
	for(i=0;i<n;i++)
		a[i] = rand()%n;
	omp_set_dynamic(0);
	omp_set_num_threads(numthrds);
	gettimeofday(&start_tv,NULL);
	if(option==1)
	b = find_first_sequential(a,target,n);
	else
	{
		#pragma omp parallel
		{
			#pragma omp single
			b = find_first(a,target,0,n-1);

		}
	}
	gettimeofday(&tv,NULL);
	double elaspsed = (double)(tv.tv_sec - start_tv.tv_sec) + (double)(tv.tv_usec -start_tv.tv_usec)/1000000;
	printf("%f\n",elaspsed);
	return 0;
}


int find_first(int *a,int target,int start,int end)
{
	int found=-1,b,c,i;
	if(end-start<=granularity)
	{
		#pragma omp parallel for schedule(dynamic,1000) default(shared) reduction(min:found)
		for(i=start;i<end;i++)
		{
			if(a[i]==target)
			{
				found = i;
			}
			
		}
		return found;
	}
	else
	{
		#pragma omp task shared(b)
		b = find_first(a,target,start,(start+end)/2);
		#pragma omp task shared(c)
		c = find_first(a,target,(start+end)/2,end);
		#pragma omp taskwait
		if(b!=-1)
		return b;
		if(c!=-1)
		return c;
		else
		return -1;
	}
}

int find_first_sequential(int *a,int target,int n)
{
	return search(a,0,n,n,target);
}

int search(int *a,int start, int end,int n,int target)
{
	int i,index=n+1;
	if(end > n)
	end = n;
	for(i=start;i<end;i++)
	{
		if(a[i]==target&&index>i)
		{
			index=i;
			
		}
		
	}
	if(index!=n+1)
	return index;
	else
	return n+1;
}
