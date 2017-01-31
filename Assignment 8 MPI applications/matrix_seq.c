#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/time.h>
int main(int argc,char *argv[])
{
int i ,*a, *x, N=3, *c,j,Idx=20,leader=0,p_row,p_column;
struct timeval tv;
struct timeval start_tv;

if(argc!=2)
{
	printf("Few number of parameters..exiting\n");
     	exit(0);
}
N = atoi(argv[1]);
a = (int *)calloc(N*N,sizeof(int));
x = (int *)calloc(N,sizeof(int));
c = (int *)calloc(N,sizeof(int));
if(a==NULL||x==NULL||c==NULL)
{
	printf("Error in alocating %fGB memory...Exiting\n",(float)(sizeof(int)*N*N)/(1024*1024*1024));
     	exit(0);
}
gettimeofday(&start_tv,NULL);
while(Idx>0)
{
	for(i=0;i<N;i++)
	{
		for(j=0;j<N;j++)
		{
			c[i] = x[i] + a[i*N+j];
		}
	}
	for(i=0;i<N;i++)
	{
		x[i] = c[i];
	}
	Idx--;
}
gettimeofday(&tv,NULL);
double elaspsed = (double)(tv.tv_sec - start_tv.tv_sec) + (double)(tv.tv_usec -start_tv.tv_usec)/1000000;
printf("%f",elaspsed);
return 0;
}
