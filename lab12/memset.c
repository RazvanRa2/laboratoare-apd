#include<string.h>
#include<stdio.h>
#include <stdlib.h>
#include<time.h>
#include <pthread.h>
#include <math.h>
/**
 * @author cristian.chilipirea
 * 
 */

int n1GB = 1024*1024*1024;
char v[1024*1024*1024];
int p;
int N = 32;
void* func(void* tid) {
	int i;
	int thread_id = (int) tid;
	int end = ((int)(fmin(ceil(N / p) * (thread_id + 1), N)));
	int start = (int)(ceil(N / p) * thread_id);

	for (i = start; i < end; i++)
		memset(v + (i * 32 * 1024 * 1024), '1', 32 * 1024 * 1024);
}
int main(int argc, char * argv[]) {
	int c;
	memset(v, '1', n1GB);

	clock_t begin = clock();

	p = atoi(argv[1]);
	pthread_t threads[atoi(argv[1])];
	for (int i = 0; i < atoi(argv[1]); i++)
	{
		int rc = pthread_create(&threads[i], NULL, func, (void *)i);
	}




	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	printf("%f\n",time_spent);

	for (int i = 0; i < atoi(argv[1]); i++)
	{
		pthread_join(threads[i], NULL);	
	}
	return 0;
}