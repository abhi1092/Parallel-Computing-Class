#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
using namespace std;

int lenght = 10;

struct node{
int data;
struct node *bck_ptr;
};
typedef struct node node;


node* intinalize();
node* search_link(node *ptr, int key);
void insert_link(node *ptr, int key);

int main(int argc, char *argv[]) {
    node *ptr,*temp;
    ptr = intinalize();
    temp = ptr;
    int I,S;
    I = atoi(argv[1]);
    S = atoi(argv[2]);

    for(int i=0;i<I;i++)
    {
        insert_link(ptr,rand());

    }
    clock_t begin = clock();
    
    for(int i=0;i<S;i++)
    {

        temp = search_link(ptr,30);

    }
    clock_t end = clock();
    
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("%d %f\n",S,time_spent);
	
   
    return 0;
}
node* intinalize()
{
    node *ptr;
    ptr = (struct node*) malloc(sizeof(struct node));

    ptr->data=18;
    ptr->bck_ptr=NULL;
    node *temp,*temp1;
    temp1=ptr;
  /*  for(int i=0;i<lenght;i++)
    {

        temp = (node*) malloc(sizeof(node));
        temp->data = i;
        temp1->bck_ptr = temp;
        temp->bck_ptr = NULL;
        temp1 = temp;
    }
*/
    return ptr;

}

node* search_link(node *ptr, int key)
{
    while(ptr->bck_ptr!=NULL)
    {
        if(ptr->data==key)
        return ptr;
        ptr = ptr->bck_ptr;
    }
    return NULL;
}

void insert_link(node *ptr, int key)
{
    while(ptr->bck_ptr!=NULL)
        ptr = ptr->bck_ptr;


    node *temp;
    temp = (node*) malloc(sizeof(node));

    temp->data = key;
    ptr->bck_ptr = temp;
    temp->bck_ptr = NULL;

}
