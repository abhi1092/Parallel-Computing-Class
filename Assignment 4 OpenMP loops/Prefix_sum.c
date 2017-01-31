#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<sys/time.h>
#include<omp.h>
void prefix_sum(int *a, int *c,  int n, int numthrds);
void prefix_sum_sequential( int *a, int *c,  int n);
int main(int argc,char *argv[])
{

	 int *a,*b,*c,n=16,mode=1,i;
	int numthrds;
	struct timeval tv;
	struct timeval start_tv;
	if(argc!=4)
	{
		printf("Few number of parameters..exiting");
		exit(0);
	}
	numthrds = atoi(argv[1]);
	n = atoi(argv[2]);
	mode =  atoi(argv[3]);
	a = ( int *)calloc(n,sizeof( int));
	c = ( int *)calloc(n,sizeof( int));
	if(a==NULL||c==NULL)
	{
	printf("Memory allocation failed");
	return 0;
	}
	for(i=0;i<n;i++)
	{
		
		a[i] = i;
		c[i] = i;
	}
	gettimeofday(&start_tv,NULL);
	if(mode==1)
	prefix_sum_sequential(a,c,n);
	else
	prefix_sum(a,c,n,numthrds);
	gettimeofday(&tv,NULL);
	double elaspsed = (double)(tv.tv_sec - start_tv.tv_sec) + (double)(tv.tv_usec -start_tv.tv_usec)/1000000;
	printf("%f",elaspsed);
	free(a);
	free(c);
	return 0;

}


void prefix_sum( int *a, int *c,  int n,int numthrds)
{
	 int i,j,power=4,d=0,l;
	
	omp_set_dynamic(0);
	omp_set_num_threads(numthrds);	
	//Prefix sum Two pass method
	//Pass one
	while(d<power)
	{
		l = pow(2,d);
		#pragma omp parallel for default(shared)
		for(i=l-1;i<n-l;i=i+l*2)
		{
			
			c[i+l] = a[i] + a[i+l];

		}
		#pragma omp parallel for default(shared)
		for(i=0;i<n;i++)
		{
			
			a[i] = c[i];
		}
		d++;
	}
	d=d-2;
	l=l/2;
	a[n-1] = 0;
	//Pass two
	while(d>-1)
	{
		#pragma omp parallel for default(shared)
		for(i=n-1;i>=l-1;i=i-2*l)
		{	
			c[i-l] = a[i];
			c[i] = a[i] + a[i-l];
		}
		l = l/2;
		#pragma omp parallel for default(shared)
		for(i=0;i<n;i++)
		{
			a[i] = c[i];
		}
		d--;
	}
	

}


void prefix_sum_sequential( int *a, int *c,  int n)
{
	 int i,j,power=4,d=0,l;
	 //Prefix sum Two pass method
	//Pass one
	while(d<power)
	{
		l = pow(2,d);
		for(i=l-1;i<n-l;i=i+l*2)
		{
			
			c[i+l] = a[i] + a[i+l];
			
		}
		
		for(i=0;i<n;i++)
		{
			
			a[i] = c[i];
		}
		d++;
	}

	a[n-1] = 0;
	d=d-2;
	l=l/2;
	//Pass two
	while(d>-1)
	{
		
		for(i=n-1;i>=l-1;i=i-2*l)
		{	
			
			c[i-l] = a[i];
			c[i] = a[i] + a[i-l];

		}
		l = l/2;
		
		for(i=0;i<n;i++)
		{
			a[i] = c[i];
		}
		d--;
	}
	

}

