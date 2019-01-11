#include<string.h>
#include<stdio.h>
#include<time.h>
#include<math.h>
#include <pthread.h>
#include <stdlib.h>

/**
 * @author cristian.chilipirea
 * 
 */

int n = 1024*1024*100;
int threadcnt;
int a;

void* func(void *tid) {
	int c;
	for (int i = 0; i < n / threadcnt; i++)
		c = sqrt(a);
}
int main(int argc, char * argv[]) {
	int i, j;

	threadcnt = atoi(argv[1]);
	pthread_t threads[atoi(argv[1])];
	for (int i = 0; i < atoi(argv[1]); i++)
	{
		int rc = pthread_create(&threads[i], NULL, func, (void *)i);
	}

	for (int i = 0; i < atoi(argv[1]); i++) {
		pthread_join(threads[i], NULL);
	}

	return 0;
}