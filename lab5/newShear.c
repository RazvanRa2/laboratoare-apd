#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int NReps;
int printLevel;
int N;
int p;
int** v;
int *vQSort;
int *vNew;
static pthread_barrier_t barrier;

void getArgs(int argc, char **argv)
{
	if(argc < 4) {
		printf("Not enough paramters: ./program N NReps no_threads\n");
		exit(1);
	}
	N = atoi(argv[1]);
	NReps = atoi(argv[2]);
    p = atoi(argv[3]);
}

void init()
{
	int i;
	v =(int **) malloc(sizeof(int *) * N);
	srand(42);
	for(i = 0; i < N; i++) {
		v[i] =(int *) malloc(sizeof(int) * N);
		for (int j = 0; j < N; j ++)
			v[i][j] = rand()%(N * N);
	}
}

void printPartial()
{
	for (int i = 0; i < N; i ++) {
		for (int j = 0; j < N; j ++) {
			printf("%d ", v[i][j]);
		}
		printf("\n");
	}
}

void print()
{
		printPartial();
}

int compareAsc (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

int compareDesc (const void * a, const void * b)
{
  return ( *(int*)b - *(int*)a );
}


void * threadFunction(void *var) {
	int thread_id = *(int*)var;

	int start = ceil((float)N/p) * thread_id;
	int end = fmin(ceil((float)N / p) * (thread_id + 1), N);

    for (int k = 0; k < log2(N); k ++) {
    	for (int i = start; i < end; i ++) {
    		if (i % 2) {
    			qsort(v[i], N, sizeof(int), compareDesc);
			} else {
    			qsort(v[i], N, sizeof(int), compareAsc);
			}
    	}
    	pthread_barrier_wait(&barrier);
    	for (int i = start; i < end; i ++) {
			int *buff = (int*)malloc(N * sizeof(int));
			for (int j = 0; j < N; j ++)
				buff[i] = v[j][i];
			qsort(buff, N, sizeof(int), compareAsc);
			for (int j = 0; j < N; j ++)
				v[j][i] = buff[j];
    	}
    	pthread_barrier_wait(&barrier);
    }
    pthread_barrier_wait(&barrier);

	return NULL;
}


int main(int argc, char *argv[])
{
	int i;
	getArgs(argc, argv);
	init();

	// make copy to check it against qsort
	// DO NOT MODIFY

    pthread_t tid[p];
    int thread_id[p];

    print();
    printf("\n");

    for (i = 0; i < p; i ++)
        thread_id[i] = i;
    pthread_barrier_init(&barrier, NULL,p );
    for(i = 0; i < p; i ++)
        pthread_create(&(tid[i]), NULL, threadFunction, &(thread_id[i]));

    for (i = 0; i < p; i ++)
        pthread_join(tid[i], NULL);

	print();

	return 0;
}
