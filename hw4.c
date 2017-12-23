
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *readerThreads(void *t)
{
	int i;
	char* fileName;
	fileName = (char*)t;
	printf("Thread %s starting\n", fileName);
	
	
	printf("Thread %s done. \n",fileName);
	pthread_exit((void*) t);
}

int main(int argc, char *argv[] ){
	int outputFile;
	char* outputFileName;
	outputFileName = argv[1];
	int filesNum = 0;
	int t = 0;
	int rc = 0;
	pthread_t* thread;
	char*

	filesNum = argc-2;
	void *status;

	printf("Hello, creating %s from %d input files\n", outputFileName , filesNum);
	outputFile = open(outputFileName, O_WRONLY | O_TRUNC);
    thread = malloc(sizeof(pthread_t)*filesNum);
	for(t=0; t<filesNum; t++)
	{
		printf("Main: creating thread %d for filename: %s \n", t, argv[t+2]);
		rc = pthread_create(&thread[t], NULL, readerThreads, (void *)argv[t+2]); 
		if (rc)
		{
			printf("ERROR in pthread_create(): %s\n", strerror(rc));
			exit(-1);
		}
	}

	for(t=0; t<filesNum; t++)
	{
		rc = pthread_join(thread[t], &status);
		if (rc)
		{
			printf("ERROR in pthread_join(): %s\n", strerror(rc));
			exit(-1);
		}
		printf("Main: completed join with thread %d having a status of %ld\n",t,(long)status);
	}
}