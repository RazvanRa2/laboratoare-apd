#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int a = 0;

void* threadFunction(void *var)
{
  pthread_mutex_lock(&lock);
	int thread_id = *(int*)var;
  for (int i = 0; i < 10000; i++) {
    a += 2;
  }
  pthread_mutex_unlock(&lock);
}

int main(int argc, char **argv)
{
	int P = 2;
	int i;
  if (pthread_mutex_init(&lock, NULL) != 0)
  {
      printf("\n mutex init failed\n");
      return 1;
  }
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
  pthread_mutex_destroy(&lock);
  printf("%d\n", a);
	return 0;
}
