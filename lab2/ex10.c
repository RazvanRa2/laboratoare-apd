#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

static pthread_barrier_t barrier;

static int numBarriers;

void* threadFunction1(void *var)
{
  int s;
    	printf("1\n");
      s = pthread_barrier_wait(&barrier);
}

void* threadFunction2(void *var)
{
      int s;
      s = pthread_barrier_wait(&barrier);
      printf("2\n");
}


int main(int argc, char **argv)
{
	int P = 2;
	int i;

	pthread_t tid[P];
	int thread_id[P];
	for(i = 0;i < P; i++)
		thread_id[i] = i;
    int s = pthread_barrier_init(&barrier, NULL, 2);
	for(i = 0; i < P; i++) {
    if (i == 0) {
		    pthread_create(&(tid[i]), NULL, threadFunction1, &(thread_id[i]));
    } else {
      pthread_create(&(tid[i]), NULL, threadFunction2, &(thread_id[i]));
    }
  }

	for(i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}

	return 0;
}
