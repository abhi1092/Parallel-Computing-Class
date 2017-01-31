#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
#include<math.h>
#include<sys/time.h>
int find_first(int *a,int n,int numthrds,int target);
int find_first_sequential(int *a,int n,int target);
int main(int argc,char *argv[])
{
	int i,arr_size=24,result,numthrds=8,target=23,mode=1;
	int *a;
	struct timeval tv;
	struct timeval start_tv;
	if(argc!=4)
	{
		printf("Few number of parameters..exiting");
		exit(0);
	}
	arr_size = atoi(argv[1]);
	numthrds = atoi(argv[2]);
	mode = atoi(argv[3]);
	a = (int *)calloc(arr_size,sizeof(int));
	if(a==NULL)
	{
		printf("Error in allocating memory. Exiting..");
		exit(0);
	}
	for(i=0;i<arr_size;i++)
	{
		a[i] = i;
	}
	gettimeofday(&start_tv,NULL);
	if(mode==1)
	result = find_first(a,arr_size,numthrds,target);
	else
	result = find_first_sequential(a,arr_size,target);
	gettimeofday(&tv,NULL);
	double elaspsed = (double)(tv.tv_sec - start_tv.tv_sec) + (double)(tv.tv_usec -start_tv.tv_usec)/1000000;
	printf("%f",elaspsed);
	free(a);
	return 0;
}






int find_first(int *a,int n,int numthrds,int target)
{
	int i,l,ptr=0,j,start,end,k,result,index;
	int *c;
	c = (int *)calloc(n,sizeof(int));
	for(i=0;i<n;i++)
	{
		c[i] = n+1;
	}

	l =  log(n)/log(2)+1;
	omp_set_dynamic(0);
	omp_set_num_threads(numthrds);

	for(i=1;i<n;i++)
	{
		
		ptr = 0;
		for(k=0;k<i;k++)
			ptr = ptr + k;
			start = ptr;
		if(ptr>n)
			break;
		if((start+i)<n)
			end = start + i;
		else
			end = n;
	#pragma omp parallel for  	
		for(j=start;j<end;j++)
		{
			//printf("In thread %d\n",omp_get_thread_num());
			if(a[j]==target)
			{
				
				c[j] = j;
			}
			
		}
		
	}
	
	
	result = c[0];
	

#pragma omp parallel for reduction(min:index)
	for(i=0;i<n;i++)
	{
		if(c[i]<result)
		{
			result = c[i];
			
		}
	}
	
	free(c);
	return result;

}

int find_first_sequential(int *a,int n,int target)
{
	int i,l,ptr=0,j,start,end,k,result,index;
	int *c;
	c = (int *)calloc(n,sizeof(int));
	for(i=0;i<n;i++)
	{
		c[i] = n+1;
	}

	l =  log(n)/log(2)+1;
	for(i=1;i<n;i++)
	{
		
		ptr = 0;
		for(k=0;k<i;k++)
			ptr = ptr + k;
			start = ptr;
		if(ptr>n)
			break;
		if((start+i)<n)
			end = start + i;
		else
			end = n;	
		for(j=start;j<end;j++)
		{
			if(a[j]==target)
			{
				c[j] = j;
			}
		
		}
		
	}
	
	
	result = c[0];


	for(i=0;i<n;i++)
	{
		if(c[i]<result)
		{
			result = c[i];
			
		}
	}
	free(c);
	return result;

}
