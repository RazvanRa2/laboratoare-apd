#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

static pthread_barrier_t barrier1;
static pthread_barrier_t barrier2;

int a;

void* threadFunction1(void *var)
{
    int s;
    s = pthread_barrier_wait(&barrier1);
    a = 5;
    s = pthread_barrier_wait(&barrier2);
    a += 7;
}

void* threadFunction2(void *var) {
    int s;
    a = 3;
    s = pthread_barrier_wait(&barrier1);
    s = pthread_barrier_wait(&barrier2);
    a += 2;
}

int main(int argc, char **argv)
{
	int P = 2;
	int i;

	pthread_t tid[P];
	int thread_id[P];
	for(i = 0;i < P; i++) {
		thread_id[i] = i;
    }
    int s1 = pthread_barrier_init(&barrier1, NULL, 2);
    int s2 = pthread_barrier_init(&barrier2, NULL, 2);

	for(i = 0; i < P; i++) {
        if (i % 2 == 0)
		    pthread_create(&(tid[i]), NULL, threadFunction1, &(thread_id[i]));
        else
            pthread_create(&(tid[i]), NULL, threadFunction2, &(thread_id[i]));
	}

	for(i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}

    printf("%d\n", a);

    return 0;
}
