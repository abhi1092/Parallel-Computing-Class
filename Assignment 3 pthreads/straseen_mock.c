#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
int op_in;

int add(int,int);
int mul(int,int);

int main(int argc, char* argv[])
{
	struct timeval tv;
	struct timeval start_tv;
	int M[7];
	int N[7];
	int P[7];
	int T[3];
	int c[2][2];
	int i;
	gettimeofday(&start_tv,NULL);
	if(argc!=2)
	{
		exit(0);
	}
	op_in = atoi( argv[1] );
	
	
	//Compute all M and N;

	for(i = 0;i<7;i++)
	{
		M[i] = add(rand(),rand());
		N[i] = add(rand(),rand());	
	}

	for(i = 0;i<7;i++)
	{
		P[i] = mul(M[i],N[i]);
	}
	
	//Comput T
	T[0] = add(P[0] , P[3]);
	T[1] = add(T[0] , P[4]);
	T[2] = add(T[0] , P[3]);

	//Compute result 2x2 Matrix
	c[0][0] = add(P[0] , P[1]);
	c[0][1] = add(P[6] , T[2]);
	c[1][0] = add(T[1] , P[6]);
	c[1][1] = add(P[3] , T[1]);

	gettimeofday(&tv,NULL);
	double elaspsed = (double)(tv.tv_sec - start_tv.tv_sec) + (double)(tv.tv_usec -start_tv.tv_usec)/1000000;
	printf("%f",elaspsed);

	return 0;
}



int add(int a, int b)
{
int i,c;
	for(i = 0;i<op_in*1;i++)
	{
		c = a+b;
	}
	return c;
}

int mul(int a, int b)
{
	int i,c;
	for(i = 0;i<op_in*3;i++)
	{
		c = a*b;
	}
	return c;

}


