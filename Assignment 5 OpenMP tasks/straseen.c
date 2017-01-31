#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/time.h>
#include<omp.h>
//Numberof Threads
int numthrds;
int option;
//Opeartion intensty. This Varibale value is assigned through parameter.
int operation_intensity;

//This variable holds amount of work. Worker threads will not exit unitl this varible becomes 0.
int work = 0; 

//Datastructure for task. It contains (1)identifer (2)Status (R-Running N-Not_Running C-Completed)
//(3)Predecessor-Holds number of predecessor tasks (4)Function pointer (5)Parameter 1 and 2 
//(6) Pointer to Successsor Task
struct task{
char identifier[3];
char status[1];
int predecessor;
int (*function_ptr)(int,int);
struct param *ptr;
struct task* successor1;
struct task* successor2;
};

//Data Structure for Exectution Queue
struct queue{
struct task *data;
struct queue *nxt;
};
//Pointer to start of queue
struct queue *execution_q;

//push_q() function to add data to queue.
void push_q(struct task* );

//pop() function removes data from queue. This Function will remove task whose status is N. If queue has no such 
//Task then it wll return NULL
struct task *pop();

//Find() function searches the queue for particukar task and return pointer to that task. The search key is 
//identifier string eg. 'M1','P1'
struct task* find(char arr[]);

//function for Master Thread. The Master Thread is responsible for Creation of worker Thread.
void master_thread_function();

//Function For worker Thread. The worker threads are created by master thread.
void strassen();
void strassen_sequential();
struct task *get_next_task();

//Function to add and Multiply. This function use operation intensity to increase computation.
int add(int,int);
int mul(int,int);

int main(int argc, char *argv[])
{
	if(argc!=4)
	{
		printf("Wrong number of arguments...Exiting");
		exit(0);
	}
	numthrds = atoi(argv[1]);
	operation_intensity = atoi(argv[2]);
	option = atoi(argv[3]);
	master_thread_function();
	return 0;
	
}


void master_thread_function()
{
	struct timeval tv;
	struct timeval start_tv;
	int i=0;
	//printf("\n Master thread started\n");
	struct task *task1;	
	struct task *temp;
	execution_q = NULL;
//Initialize Tasks
	//initilize tasks M1 and add to execution queue
	task1 = (struct task *) malloc(sizeof(struct task));
	task1->identifier[0] = 'M' ; 
	task1->identifier[1] = '1' ;
	task1->identifier[2] = '\0' ;
	task1->function_ptr = add;
	task1->predecessor = 0;
	task1->ptr = NULL;
	task1->status[0] = 'N';
	push_q(task1);
	
	//initilize tasks M1 and add to execution queue
	task1 = (struct task *) malloc(sizeof(struct task));
	task1->identifier[0] = 'M' ; 
	task1->identifier[1] = '2' ;
	task1->identifier[2] = '\0' ;
	task1->function_ptr = add;
	task1->predecessor = 0;
	task1->ptr = NULL;
	task1->status[0] = 'N';
	push_q(task1);

	//initilize tasks M3 and add to execution queue
	task1 = (struct task *) malloc(sizeof(struct task));
	task1->identifier[0] = 'M' ; 
	task1->identifier[1] = '3' ;
	task1->identifier[2] = '\0' ;
	task1->function_ptr = add;
	task1->predecessor = 0;
	task1->ptr = NULL;
	task1->status[0] = 'N';
	push_q(task1);

	
	//initilize tasks M4 and add to execution queue
	task1 = (struct task *) malloc(sizeof(struct task));
	task1->identifier[0] = 'M' ; 
	task1->identifier[1] = '4' ;
	task1->identifier[2] = '\0' ;
	task1->function_ptr = add;
	task1->predecessor = 1;
	task1->ptr = NULL;
	task1->status[0] = 'N';
	push_q(task1);
	
	//initilize tasks M5 and add to execution queue
	task1 = (struct task *) malloc(sizeof(struct task));
	task1->identifier[0] = 'M' ; 
	task1->identifier[1] = '5' ;
	task1->identifier[2] = '\0' ;
	task1->function_ptr = add;
	task1->predecessor = 0;
	task1->ptr = NULL;
	task1->status[0] = 'N';
	push_q(task1);
	
	//initilize tasks M6 and add to execution queue
	task1 = (struct task *) malloc(sizeof(struct task));
	task1->identifier[0] = 'M' ; 
	task1->identifier[1] = '6' ;
	task1->identifier[2] = '\0' ;
	task1->function_ptr = add;
	task1->predecessor = 0;
	task1->ptr = NULL;
	task1->status[0] = 'N';
	push_q(task1);

	//initilize tasks M7 and add to execution queue
	task1 = (struct task *) malloc(sizeof(struct task));
	task1->identifier[0] = 'M' ; 
	task1->identifier[1] = '7' ;
	task1->identifier[2] = '\0' ;
	task1->function_ptr = add;
	task1->predecessor = 0;
	task1->ptr = NULL;
	task1->status[0] = 'N';
	push_q(task1);

	//initilize tasks N1 and add to execution queue
	task1 = (struct task *) malloc(sizeof(struct task));
	task1->identifier[0] = 'N' ; 
	task1->identifier[1] = '1' ;
	task1->identifier[2] = '\0' ;
	task1->function_ptr = add;
	task1->predecessor = 0;
	task1->ptr = NULL;
	task1->status[0] = 'N';
	push_q(task1);

	//initilize tasks N2 and add to execution queue
	task1 = (struct task *) malloc(sizeof(struct task));
	task1->identifier[0] = 'N' ; 
	task1->identifier[1] = '2' ;
	task1->identifier[2] = '\0' ;
	task1->function_ptr = add;
	task1->predecessor = 0;
	task1->ptr = NULL;
	task1->status[0] = 'N';
	push_q(task1);

	//initilize tasks N3 and add to execution queue
	task1 = (struct task *) malloc(sizeof(struct task));
	task1->identifier[0] = 'N' ; 
	task1->identifier[1] = '3' ;
	task1->identifier[2] = '\0' ;
	task1->function_ptr = add;
	task1->predecessor = 0;
	task1->ptr = NULL;
	task1->status[0] = 'N';
	push_q(task1);

	//initilize tasks N4 and add to execution queue
	task1 = (struct task *) malloc(sizeof(struct task));
	task1->identifier[0] = 'N' ; 
	task1->identifier[1] = '4' ;
	task1->identifier[2] = '\0' ;
	task1->function_ptr = add;
	task1->predecessor = 1;
	task1->ptr = NULL;
	task1->status[0] = 'N';
	push_q(task1);

	//initilize tasks N5 and add to execution queue
	task1 = (struct task *) malloc(sizeof(struct task));
	task1->identifier[0] = 'N' ; 
	task1->identifier[1] = '5' ;
	task1->identifier[2] = '\0' ;
	task1->function_ptr = add;
	task1->predecessor = 0;
	task1->ptr = NULL;
	task1->status[0] = 'N';
	push_q(task1);

	//initilize tasks N6 and add to execution queue
	task1 = (struct task *) malloc(sizeof(struct task));
	task1->identifier[0] = 'N' ; 
	task1->identifier[1] = '6' ;
	task1->identifier[2] = '\0' ;
	task1->function_ptr = add;
	task1->predecessor = 0;
	task1->ptr = NULL;
	task1->status[0] = 'N';
	push_q(task1);

	//initilize tasks N7 and add to execution queue
	task1 = (struct task *) malloc(sizeof(struct task));
	task1->identifier[0] = 'N' ; 
	task1->identifier[1] = '7' ;
	task1->identifier[2] = '\0' ;
	task1->function_ptr = add;
	task1->predecessor = 0;
	task1->ptr = NULL;
	task1->status[0] = 'N';
	push_q(task1);

	//initilize tasks N1 and add to execution queue
	task1 = (struct task *) malloc(sizeof(struct task));
	task1->identifier[0] = 'P' ; 
	task1->identifier[1] = '1' ;
	task1->identifier[2] = '\0' ;
	task1->function_ptr = mul;
	task1->predecessor = 2;
	task1->ptr = NULL;
	task1->status[0] = 'N';
	push_q(task1);

	//initilize tasks N2 and add to execution queue
	task1 = (struct task *) malloc(sizeof(struct task));
	task1->identifier[0] = 'P' ; 
	task1->identifier[1] = '2' ;
	task1->identifier[2] = '\0' ;
	task1->function_ptr = mul;
	task1->predecessor = 2;
	task1->ptr = NULL;
	task1->status[0] = 'N';
	push_q(task1);

	//initilize tasks N3 and add to execution queue
	task1 = (struct task *) malloc(sizeof(struct task));
	task1->identifier[0] = 'P' ; 
	task1->identifier[1] = '3' ;
	task1->identifier[2] = '\0' ;
	task1->function_ptr = mul;
	task1->predecessor = 2;
	task1->ptr = NULL;
	task1->status[0] = 'N';
	push_q(task1);

	//initilize tasks N4 and add to execution queue
	task1 = (struct task *) malloc(sizeof(struct task));
	task1->identifier[0] = 'P' ; 
	task1->identifier[1] = '4' ;
	task1->identifier[2] = '\0' ;
	task1->function_ptr = mul;
	task1->predecessor = 2;
	task1->ptr = NULL;
	task1->status[0] = 'N';
	push_q(task1);

	//initilize tasks N5 and add to execution queue
	task1 = (struct task *) malloc(sizeof(struct task));
	task1->identifier[0] = 'P' ; 
	task1->identifier[1] = '5' ;
	task1->identifier[2] = '\0' ;
	task1->function_ptr = mul;
	task1->predecessor = 2;
	task1->ptr = NULL;
	task1->status[0] = 'N';
	push_q(task1);

	//initilize tasks N6 and add to execution queue
	task1 = (struct task *) malloc(sizeof(struct task));
	task1->identifier[0] = 'P' ; 
	task1->identifier[1] = '6' ;
	task1->identifier[2] = '\0' ;
	task1->function_ptr = mul;
	task1->predecessor = 2;
	task1->ptr = NULL;
	task1->status[0] = 'N';
	push_q(task1);

	//initilize tasks N7 and add to execution queue
	task1 = (struct task *) malloc(sizeof(struct task));
	task1->identifier[0] = 'P' ; 
	task1->identifier[1] = '7' ;
	task1->identifier[2] = '\0' ;
	task1->function_ptr = mul;
	task1->predecessor = 2;
	task1->ptr = NULL;
	task1->status[0] = 'N';
	push_q(task1);
	

	//initilize tasks T1 and add to execution queue
	task1 = (struct task *) malloc(sizeof(struct task));
	task1->identifier[0] = 'T' ; 
	task1->identifier[1] = '1' ;
	task1->identifier[2] = '\0' ;
	task1->function_ptr = mul;
	task1->predecessor = 2;
	task1->ptr = NULL;
	task1->status[0] = 'N';
	push_q(task1);

	//initilize tasks T2 and add to execution queue
	task1 = (struct task *) malloc(sizeof(struct task));
	task1->identifier[0] = 'T' ; 
	task1->identifier[1] = '2' ;
	task1->identifier[2] = '\0' ;
	task1->function_ptr = mul;
	task1->predecessor = 2;
	task1->ptr = NULL;
	task1->status[0] = 'N';
	push_q(task1);

	//initilize tasks T3 and add to queue
	task1 = (struct task *) malloc(sizeof(struct task));
	task1->identifier[0] = 'T' ; 
	task1->identifier[1] = '3' ;
	task1->identifier[2] = '\0' ;
	task1->function_ptr = mul;
	task1->predecessor = 2;
	task1->ptr = NULL;
	task1->status[0] = 'N';
	push_q(task1);

	
	
	//initilize tasks C11 and add to execution queue
	task1 = (struct task *) malloc(sizeof(struct task));
	task1->identifier[0] = 'C' ; 
	task1->identifier[1] = '1' ;
	task1->identifier[2] = '\0' ;
	task1->function_ptr = mul;
	task1->predecessor = 2;
	task1->ptr = NULL;
	task1->status[0] = 'N';
	push_q(task1);
	
	//initilize tasks C12 and add to execution queue
	task1 = (struct task *) malloc(sizeof(struct task));
	task1->identifier[0] = 'C' ; 
	task1->identifier[1] = '2' ;
	task1->identifier[2] = '\0' ;
	task1->function_ptr = mul;
	task1->predecessor = 2;
	task1->ptr = NULL;
	task1->status[0] = 'N';
	push_q(task1);

	//initilize tasks C21 and add to execution queue
	task1 = (struct task *) malloc(sizeof(struct task));
	task1->identifier[0] = 'C' ; 
	task1->identifier[1] = '3' ;
	task1->identifier[2] = '\0' ;
	task1->function_ptr = mul;
	task1->predecessor = 2;
	task1->ptr = NULL;
	task1->status[0] = 'N';
	push_q(task1);

	//initilize tasks C22 and add to execution queue
	task1 = (struct task *) malloc(sizeof(struct task));
	task1->identifier[0] = 'C' ; 
	task1->identifier[1] = '4' ;
	task1->identifier[2] = '\0' ;
	task1->function_ptr = mul;
	task1->predecessor = 2;
	task1->ptr = NULL;
	task1->status[0] = 'N';
	push_q(task1);

//Start Adding successors
	//successor for M
	task1 = find("M1");
	task1->successor1 = find("P1");
	task1->successor2 = NULL;

	task1 = find("M2");
	task1->successor1 = find("P2");
	task1->successor2 = NULL;

	task1 = find("M3");
	task1->successor1 = find("P3");
	task1->successor2 = find("M4");

	task1 = find("M4");
	task1->successor1 = find("P4");
	task1->successor2 = NULL;

	task1 = find("M5");
	task1->successor1 = find("P5");
	task1->successor2 = NULL;

	task1 = find("M6");
	task1->successor1 = find("P6");
	task1->successor2 = NULL;

	task1 = find("M7");
	task1->successor1 = find("P7");
	task1->successor2 = NULL;

	//successor for N
	task1 = find("N1");
	task1->successor1 = find("P1");
	task1->successor2 = NULL;

	task1 = find("N2");
	task1->successor1 = find("P2");
	task1->successor2 = NULL;

	task1 = find("N3");
	task1->successor1 = find("N4");
	task1->successor2 = find("P3");

	task1 = find("N4");
	task1->successor1 = find("P4");
	task1->successor2 = NULL;

	task1 = find("N5");
	task1->successor1 = find("P5");
	task1->successor2 = NULL;

	task1 = find("N6");
	task1->successor1 = find("P6");
	task1->successor2 = NULL;

	task1 = find("N7");
	task1->successor1 = find("P7");
	task1->successor2 = NULL;

	//sucessor for P task
	task1 = find("P1");
	task1->successor1 = find("T1");
	task1->successor2 = find("C1");

	task1 = find("P2");
	task1->successor1 = find("C1");
	task1->successor2 = NULL;

	task1 = find("P3");
	task1->successor1 = find("T3");
	task1->successor2 = find("C4");

	task1 = find("P4");
	task1->successor1 = find("T1");
	task1->successor2 = NULL;

	task1 = find("P5");
	task1->successor1 = find("T2");
	task1->successor2 = NULL;

	task1 = find("P6");
	task1->successor1 = find("C2");
	task1->successor2 = NULL;

	task1 = find("P7");
	task1->successor1 = find("C3");
	task1->successor2 = NULL;

	//successor for T
	task1 = find("T1");
	task1->successor1 = find("T2");
	task1->successor2 = find("T3");

	task1 = find("T2");
	task1->successor1 = find("C3");
	task1->successor2 = find("C4");

	task1 = find("T3");
	task1->successor1 = find("C2");
	task1->successor2 = NULL;
	
	//Successor for C
	task1 = find("C1");
	task1->successor1 = NULL;
	task1->successor2 = NULL;

	task1 = find("C2");
	task1->successor1 = NULL;
	task1->successor2 = NULL;

	task1 = find("C3");
	task1->successor1 = NULL;
	task1->successor2 = NULL;

	task1 = find("C4");
	task1->successor1 = NULL;
	task1->successor2 = NULL;
	gettimeofday(&start_tv,NULL);

	omp_set_num_threads(numthrds);
	if(option==1)
	{
		strassen_sequential();
	}
	else
	{
		//Execute Strassen
		#pragma omp parallel
		{
			#pragma omp single
			strassen();

		}
	}
	
		
	gettimeofday(&tv,NULL);
	double elaspsed = (double)(tv.tv_sec - start_tv.tv_sec) + (double)(tv.tv_usec -start_tv.tv_usec)/1000000;
	printf("%f",elaspsed);
	
	
}


void strassen()
{
	struct task* temp,*succ1,*succ2;
	//printf("Worker Thread Started\n");

	while(1)
	{
		
		temp = get_next_task();
		if(temp==NULL)
		break;
	
		//printf("Executing %s\n",temp->identifier);
		#pragma omp task
		temp->function_ptr(rand(),rand());
		
		if(temp->successor1!=NULL)
		{
			temp->successor1->predecessor--;
		
			if(temp->successor1->predecessor==0)
			{
				succ1 = temp->successor1;
				succ1->status[0] = 'R';
				//Execute Successor
				if(succ1->successor1!=NULL)
					succ1->successor1->predecessor--;
				if(succ1->successor2!=NULL)
					succ1->successor2->predecessor--;
			
				
				//printf("Executing %s\n",succ1->identifier);
				#pragma omp task
				succ1->function_ptr(rand(),rand());
			}
			
		}
		if(temp->successor2!=NULL)
		{
			temp->successor2->predecessor--;
			
			if(temp->successor2->predecessor==0)
			{
				succ2 = temp->successor2;
				succ2->status[0] = 'R';
				//Execute Successor
				if(succ2->successor1!=NULL)
					succ2->successor1->predecessor--;
				if(succ2->successor2!=NULL)
					succ2->successor2->predecessor--;
				
				//printf("Executing %s\n",succ2->identifier);
				#pragma omp task
				succ2->function_ptr(rand(),rand());
				
			}
			
		}
		
		

	}

	#pragma omp taskwait

}


void strassen_sequential()
{
	struct task* temp,*succ1,*succ2;
	//printf("Worker Thread Started\n");

	while(1)
	{
		
		temp = get_next_task();
		if(temp==NULL)
		break;
	
		//printf("Executing %s\n",temp->identifier);
		temp->function_ptr(rand(),rand());
		
		if(temp->successor1!=NULL)
		{
			temp->successor1->predecessor--;
		
			if(temp->successor1->predecessor==0)
			{
				succ1 = temp->successor1;
				succ1->status[0] = 'R';
				//Execute Successor
				if(succ1->successor1!=NULL)
					succ1->successor1->predecessor--;
				if(succ1->successor2!=NULL)
					succ1->successor2->predecessor--;
			
				
				//printf("Executing %s\n",succ1->identifier);
				succ1->function_ptr(rand(),rand());
			}
			
		}
		if(temp->successor2!=NULL)
		{
			temp->successor2->predecessor--;
			
			if(temp->successor2->predecessor==0)
			{
				succ2 = temp->successor2;
				succ2->status[0] = 'R';
				//Execute Successor
				if(succ2->successor1!=NULL)
					succ2->successor1->predecessor--;
				if(succ2->successor2!=NULL)
					succ2->successor2->predecessor--;
				
				//printf("Executing %s\n",succ2->identifier);
				succ2->function_ptr(rand(),rand());
				
			}
			
		}
		
		

	}

	

}

struct task *get_next_task()
{
return pop();
}


int add(int a, int b)
{
	int k=0,c=0;
	
	while(k<operation_intensity*4)
	{
		c = c+a+b;
		k++;
	}
	return c;
}

int mul(int a, int b)
{
	int k=0,c;
	while(k<(operation_intensity*5))
	{
		c = c+a*b;
		k++;
	}
	return c;
}

void push_q(struct task* temp1)
{
	struct queue *temp;
	
	if(execution_q==NULL)
	{
		execution_q = (struct queue*) malloc( sizeof(struct queue) );
		execution_q->data = temp1;
		execution_q->nxt = NULL;
		
	}
	else
	{
		temp = execution_q;
		while(temp->nxt!=NULL)
		{
		
		temp = temp->nxt;
		}
		temp->nxt = (struct queue*) malloc( sizeof(struct queue) );
		temp = temp->nxt;
		temp->data = temp1;
		temp->nxt = NULL;
		
		
	}

}

struct task *pop()
{
	
	struct queue* temp;
	temp = execution_q;
	if(execution_q==NULL)
	return NULL;
	else
	{
		
		while(temp!=NULL)
		{
			
			if(temp->data->status[0]=='N' && temp->data->predecessor==0)
			{
				break;
			}
			
			temp = temp->nxt;
			
		}
		if(temp==NULL)
		{
			return NULL;
		}
		else
		{
			temp->data->status[0] = 'R';
			return temp->data;
		}
		
		
		
	}
}

struct task* find(char arr[])
{
	struct queue* temp;
	temp = execution_q;
	while(temp!=NULL)
	{
		if( strcmp(temp->data->identifier,arr)==0)
			break;
		
		temp = temp->nxt;
	}	
	return temp->data;
}


