#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

void* threadFunction(void *var)
{
	int thread_id = *(int*)var;

	for (int i = 0; i <= 2^30; i ++) {
		for (int i1 = 0; i1 <= 2^30; i1 ++)
			for (int i2 = 0; i2 <= 2^30; i2 ++)
				for (int i3 = 0; i3 <= 2^30; i3 ++)
		sqrt(sqrt(sqrt(i)));
	}

	printf("Hello world from thread %i\n", thread_id);
}

int main(int argc, char **argv)
{
	int P = 4;
	int i;

	pthread_t tid[P];
	int thread_id[P];
	for(i = 0;i < P; i++)
		thread_id[i] = i;

	for(i = 0; i < P; i++) {
		pthread_create(&(tid[i]), NULL, threadFunction, &(thread_id[i]));
	}

	for(i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}

	return 0;
}
threa