#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int a = 0;

void* threadFunction(void *var)
{
    int thread_id = *(int*)var;
    for (int i = 0; i < 100; i++) {
        a += 2;
    }
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

	for(i = 0; i < P; i++) {
        pthread_create(&(tid[i]), NULL, threadFunction, &(thread_id[i]));
	}

	for(i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}

    printf("%d\n", a);

    return 0;
}

/*
    Smallest value that can be displayed is 200.
    This would happen if execution would go down like this:
    a = 0
    thread 1: reads a
    thread 2: reads a
    thread 1: sets a to 2
    thread 2: sets a to 2
    thread 1: counter++
    thread 2: counter++
    loop from line 44 untill counter reaches 100
*/
