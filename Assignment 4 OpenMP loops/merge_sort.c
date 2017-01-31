#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<math.h>
#include<sys/time.h>
void merge_sort(int *a,int *c,int n, int numthrds);
void merge_sort_sequential(int *a,int *b,int n);
int main(int argc,char *argv[])
{
	int *a,*b,n,i,mode;
	int numthrds =16;
	struct timeval tv;
	struct timeval start_tv;
	if(argc!=4)
	{
		printf("Few number of parameters..exiting");
		exit(0);
	}
	numthrds = atoi(argv[1]);
	n = atoi(argv[2]);
	mode = atoi(argv[3]);
	a = (int *)calloc(n,sizeof(int));
	b = (int *)calloc(n,sizeof(int));
	if(a==NULL||b==NULL)
	{
		printf("Error in Memory Allocation");
		exit(0);
	}
	gettimeofday(&start_tv,NULL);
	if(mode==1)
	merge_sort_sequential(a,b,n);
	else
	merge_sort(a,b,n,numthrds);
	gettimeofday(&tv,NULL);
	double elaspsed = (double)(tv.tv_sec - start_tv.tv_sec) + (double)(tv.tv_usec -start_tv.tv_usec)/1000000;
	printf("%f",elaspsed);
	free(a);
	free(b);
	return 0;
}


void merge_sort(int *a,int *b,int n, int numthrds)
{
	int i,j,p=2,power=1,start,end,start2,end2,start1,end1,ptr,test=0;
	omp_set_dynamic(0);
	omp_set_num_threads(numthrds);
	while(p<n)
	{
		p = pow(2,power++);
		start = 0;
		end = 0;
//Below loop divides the array in 'p' small arrays. Merge sort is performed on 1 to p/2 and p/2 to p. The value of p increases from 2 to log(n) 
		#pragma omp parallel for default(shared) private(start,start1,start2,end1,end2,end,ptr,j)
		for(i=0;i<n;i=i+p)
		{
			
			start=i;
			end = i+p-1;
			start1 = start;
			end1 = start1 + (end-start)/2;
			start2 = end1+1;
			end2 = end;
			ptr = start;
			for(j=0;j<p;j++)
			{
				
				
				if(start1>end1||start2>end2)
				{
					continue;
				}
				if(a[start1]==a[start2])
				{
					
					b[ptr++] = a[start2++];
					b[ptr++] = a[start1++];	
					
				}
				else
				{
					if(a[start1]>=a[start2])
					{
						b[ptr++] = a[start2++];
					}
					else
					{
						b[ptr++] = a[start1++];
					}
					
					
					
				}
			}
			
			for(j=start1;j<=end1;j++)
			{
				b[ptr++] = a[j];
			}
		
			for(j=start2;j<=end2;j++)
			{
				b[ptr++] = a[j];
			}

			
		}
		#pragma omp parallel for default(shared)
		for(i=0;i<n;i++)
		{
			
			a[i] = b[i];
		}
		
	}	
}


void merge_sort_sequential(int *a,int *b,int n)
{
int i,j,p=2,power=1,start,end,start2,end2,start1,end1,ptr,test=0;
	
	while(p<n)
	{
		p = pow(2,power++);
		start = 0;
		end = 0;
//Below loop divides the array in 'p' small arrays. Merge sort is performed on 1 to p/2 and p/2 to p. The value of p increases from 2 to log(n) 
		for(i=0;i<n;i=i+p)
		{
			
			start=i;
			end = i+p-1;
			start1 = start;
			end1 = start1 + (end-start)/2;
			start2 = end1+1;
			end2 = end;
			
			ptr = start;
	
			for(j=0;j<p;j++)
			{
				
				
				if(start1>end1||start2>end2)
				{
					continue;
				}
				if(a[start1]==a[start2])
				{
					
					b[ptr++] = a[start2++];
					b[ptr++] = a[start1++];	
					
				}
				else
				{
					if(a[start1]>=a[start2])
					{
						b[ptr++] = a[start2++];
					}
					else
					{
						b[ptr++] = a[start1++];
					}
					
					
					
				}
			}
		
			for(j=start1;j<=end1;j++)
			{
				b[ptr++] = a[j];
			}
			
			for(j=start2;j<=end2;j++)
			{
				b[ptr++] = a[j];
			}
		
		}
		
		for(i=0;i<n;i++)
		{
			
			a[i] = b[i];
		}
		
	}	
}
