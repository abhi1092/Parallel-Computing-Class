#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<float.h>
#include<time.h>
#include<sys/time.h>
using namespace std;
int a,b,n,k;
int op;
int integrate();
int find_pow(int);
int find_sqrt(int);
int main(int argc, char* argv[])
{
	struct timeval tv;
	struct timeval start_tv;
	float I;
	a = atoi(argv[1]);
	b = atoi(argv[2]);
	n = atoi(argv[3]);
	op = atoi(argv[4]);
	gettimeofday(&start_tv,NULL);
	I = integrate();
	gettimeofday(&tv,NULL);
	double elaspsed = (double)(tv.tv_sec - start_tv.tv_sec) + (double)(tv.tv_usec -start_tv.tv_usec)/1000000;
	printf("%f",elaspsed);
	return 0;

}


int integrate()
{
float  I = 0,x,f;
for(int i=0;i<n;i++)
	{
		x = a+(i+0.5)*(b-a)/n;	
		f = find_sqrt(x);
		f = find_pow(f);
		I = I + f*(b-a)/n;	
	}
	return I;
}

int find_sqrt(int x)
{
float f;
int k = 0;
	f = x;
	while(k < op)
	{
		f = sqrt(f);
		k++;
	}
	return f;
}
int find_pow(int x)
{
	int k = 0;
	float f;
	f = x;
	while(k < op)
	{
		f = pow(f,1000);
		k++;
	}
	return f;
}
