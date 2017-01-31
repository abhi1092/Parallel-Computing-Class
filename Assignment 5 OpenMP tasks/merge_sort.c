#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<time.h>
#include<sys/time.h>
int granularity;
void merge_sort(int *a, int start, int end);
void merge_sort_sequential(int *a, int start, int end);
void merge(int *a, int start, int end);
int main(int argc,char *argv[])
{
	int *a,n=10,i,numthrds,option;
	struct timeval tv;
	struct timeval start_tv;
	if(argc!=4)
	{
		printf("Few number of parameters..exiting");
		exit(0);
	}
	numthrds = atoi(argv[1]);
	n = atoi(argv[2]);
	option = atoi(argv[3]);
	granularity = 1;
	a = (int *) calloc(n,sizeof(int));
	if(a==NULL)
	{
		printf("Error in allocating memory");
		exit(0);
	}
	for(i=0;i<n;i++)
		a[i] = rand()%n;
	gettimeofday(&start_tv,NULL);
	if(option==1)
	{
		merge_sort_sequential(a,0,n-1);
	}
	else
	{
		omp_set_num_threads(numthrds);
		#pragma omp parallel
		{
			#pragma omp single
			merge_sort(a,0,n-1);

		}
	}
	gettimeofday(&tv,NULL);
	double elaspsed = (double)(tv.tv_sec - start_tv.tv_sec) + (double)(tv.tv_usec -start_tv.tv_usec)/1000000;
	printf("%f\n",elaspsed);
	free(a);
	return 0;
}

int min(int a,int b)
{
	if(a<b)
	return a;
	else
	return b;
}

void merge_sort(int *a, int start, int end)
{
	int start1,mid,end1,decomposition_size,size;
	//printf("In thread %d\n",omp_get_thread_num());
	//printf("start:%d end:%d\n",start,end);
	if(end-start<=granularity)
	{
                 size = end-start;
   	 	 for (decomposition_size=1; decomposition_size<=size; decomposition_size = 2*decomposition_size)
  			{
       
     			  for (start1=0; start1<size; start1 += 2*decomposition_size)
       				{
           				mid = start1 + decomposition_size - 1;
           				end1 = min(start1 + 2*decomposition_size - 1, size-1);
           				merge(a,start1,end1+1);
       				}
   			}
	}
	else
	{
		mid = (start+end)/2;
		#pragma omp task
		merge_sort(a,start,mid);
		#pragma omp task
		merge_sort(a,mid+1,end);
		#pragma omp taskwait
		merge(a,start,end);

	}
	
}

void merge(int *a, int start, int end)
{
	int start2,ptr2=0,start1,temp,i,mid,j,*b;
		mid = (start+end)/2;
		#pragma omp task
		merge_sort(a,start,mid);
		#pragma omp task
		merge_sort(a,mid+1,end);
		#pragma omp taskwait
		b = (int *) calloc((end-start)+1,sizeof(int));
		start2 = mid+1;
		start1 = start;
		for(i=start;i<end;i++)
		{
			if(start2>end||start1>mid)
			break;
			if(a[start1]>a[start2])
			{
				b[ptr2++] = a[start2++];
			}
			else
			{
				if(a[start1]<a[start2])
				{
					b[ptr2++] = a[start1++];
				}
				else
				{
					//If both of them are equal
					b[ptr2++] = a[start2++];
					b[ptr2++] = a[start1++];
				}
			}
		}
		for(j=start1;j<mid+1;j++)
		b[ptr2++] = a[j];
		for(j=start2;j<=end;j++)
		b[ptr2++] = a[j];
		ptr2=0;
		for(i=start;i<=end;i++)
		a[i] = b[ptr2++];
		free(b);

}

void merge_sort_sequential(int *a, int start, int end)
{
	int start2,ptr2=0,start1,temp,i,mid,j,*b;
	//printf("start:%d end:%d\n",start,end);
	if(end-start<=1)
	{
		if(a[start]>a[end])
		{
			temp = a[end];
			a[end] = a[start];
			a[start] = temp;
		}
	}
	else
	{
		mid = (start+end)/2;
		merge_sort_sequential(a,start,mid);
		merge_sort_sequential(a,mid+1,end);
		merge(a,start,end);
	}
	
}
