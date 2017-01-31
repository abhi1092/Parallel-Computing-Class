#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<math.h>
#include<sys/time.h>
pthread_mutex_t count_mut;
pthread_mutex_t integrate_mut;

int NUMTHRDS;
int work_done=0;
int work = 100;
double integrate = 0;
struct loop_data{
int a;
int b;
int n;
int mode;
int granularity;
int operation_intensity;
int count;
};

struct loop_data data;

void loop_get_next(int* , int* );
void * loop_schdler_slave(void *);


int main(int argc, char* argv[])
{
	struct timeval tv;
	struct timeval start_tv;
	int i=0;
	long it;
	double time_spent;
	clock_t begin,end;
	if(argc!=8)
	{
		printf("Wrong number of Arguments....Exiting\n");
		exit(0);
	}
	data.a = atoi(argv[1]);
	data.b = atoi(argv[2]);
	data.n = atoi(argv[3]);
	data.operation_intensity = atoi(argv[4]);
	data.mode = atoi(argv[5]);
	data.granularity = atoi(argv[6]);
	NUMTHRDS = atoi(argv[7]);
	work = data.n;
	pthread_t *tid;
	tid = (pthread_t*)calloc(NUMTHRDS,sizeof(pthread_t));
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_mutex_init(&count_mut,NULL);
	pthread_mutex_init(&integrate_mut,NULL);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
	gettimeofday(&start_tv,NULL);
	for(i = 0; i < NUMTHRDS; i++)
	{
		pthread_create(&tid[i], &attr, loop_schdler_slave, (void *) it);
	}
	
	for( i = 0; i< NUMTHRDS; i++)
	{
		pthread_join(tid[i],NULL);
	}
	
	end = clock();
	gettimeofday(&tv,NULL);
	double elaspsed = (double)(tv.tv_sec - start_tv.tv_sec) + (double)(tv.tv_usec -start_tv.tv_usec)/1000000;
	printf("%f",elaspsed);
	pthread_mutex_destroy(&count_mut);
	pthread_mutex_destroy(&integrate_mut);
	pthread_exit(NULL);
	
	
return 0;	
	
}

void * loop_schdler_slave(void * arg)
{
int begin,end;
int i,k=0;
double f,x=0;
double local_integrate=0;
double per_call_integrate = 0;
	//printf("Thread Started\n");
	
	while(1)
	{
		pthread_mutex_lock(&count_mut);
		loop_get_next(&begin, &end);
		pthread_mutex_unlock(&count_mut);
		if(begin==-1&&end==-1)
		{
			break;
		}
		else
		{
			
			

			//Start integration
			
			for(i = begin; i<=end;i++)
			{
				x = data.a+(i+0.5)*(data.b-data.a)/data.n;
				k = 0;
				while(k<data.operation_intensity)
				{
					f = pow(x,2);
					f = sqrt(x);
					k++;
					
				}
				if(data.mode==1)
				{
					pthread_mutex_lock(&integrate_mut);
					integrate = integrate + f*(data.b-data.a)/data.n;
					pthread_mutex_unlock(&integrate_mut);
					
				}
				if(data.mode==2)
				{
					per_call_integrate = per_call_integrate + f*(data.b-data.a)/data.n;
				}
				if(data.mode==3)
				{
					local_integrate = local_integrate + f*(data.b-data.a)/data.n;
				}
				
				

			}
			if(data.mode==2)
			{
				
				pthread_mutex_lock(&integrate_mut);
				integrate = integrate + per_call_integrate;
				pthread_mutex_unlock(&integrate_mut);
				per_call_integrate = 0;
			}

		
		}
	}
	if(data.mode==3)
	{
		
		pthread_mutex_lock(&integrate_mut);
		integrate = integrate + local_integrate;
		pthread_mutex_unlock(&integrate_mut);
	}
	pthread_exit(NULL);
	
}



void loop_get_next(int* begin, int* end)
{
	if(work<=0)
	{
		*begin = -1;
		*end = -1;
		return;
	}
	else
	{
		if(work < data.granularity)
		{
			*begin = work_done + 1;
			*end = work_done + work;
			work = 0;
			return;
		}
		
		*begin = work_done + 1;
		*end = work_done + data.granularity;
		work_done = work_done + data.granularity;
		work = work - data.granularity;
		return;				
	}

}



