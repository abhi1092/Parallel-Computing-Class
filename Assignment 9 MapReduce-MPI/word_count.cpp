#include "mpi.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "sys/stat.h"
#include "mapreduce.h"
#include "keyvalue.h"
using namespace MAPREDUCE_NS;
void mymap(int ,char *,KeyValue *,void *);

void myreduce(char *,int ,char *,int,int *,KeyValue *kv,void *);
int main(int argc,char *argv[])
{
	int p, P;
	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &p);
	MPI_Comm_size(MPI_COMM_WORLD, &P);

	MapReduce *mr = new MapReduce();
	
	MPI_Barrier(MPI_COMM_WORLD);
	//Map the Key-Value pair
	mr->map(argc-1,&argv[1],0,1,0,mymap,NULL); 
	//Collate Same key pairs to for KMV
	mr->collate(NULL);
	MPI_Barrier(MPI_COMM_WORLD);
	//Reduce the KMV pair  to form KV pair which has Word as key and Value as Count
	mr->reduce(&myreduce,NULL);
	mr->print("output_count.txt",0,-1,1,5,1);
	MPI_Finalize();
	return 0;
}

void mymap(int tasknum,char *filename,KeyValue *kv,void* ptr)
{
	//Read the file
  struct stat stbuf;
	int flag = stat(filename,&stbuf);
 	if (flag < 0) {
    		printf("ERROR: Could not query file size\n");
    		MPI_Abort(MPI_COMM_WORLD,1);
  	}
  	int filesize = stbuf.st_size;
	FILE *fn = fopen(filename,"r");
	char *text = new char[filesize+1];
  	int nchar = fread(text,1,filesize,fn);
	text[nchar] = '\0';
	fclose(fn);
	//Sperate each word with sperator  \t\n\f\r\0
	char *word = strtok(text," \t\n\f\r\0");
	while(word){
		//Make Key value pair for each word and Null value as Vaue
		kv->add(word,strlen(word)+1,NULL,0);
		word = strtok(NULL," \t\n\f\r\0");
	}
	delete [] text;
}

void myreduce(char *key,int keybyte,char *multivalue,int nvalue,int *valuebyte,KeyValue *kv,void *ptr)
{
	//Make new Key value pair such that count or Nvalue is key and value is word 
	kv->add(key,keybyte,(char *)&nvalue,sizeof(int));
}
