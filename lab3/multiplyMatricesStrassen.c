#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int NReps;
int printLevel;
int N;
int** a;
int** b;
int** c;
int** M1;
int** AUXM11;
int** AUXM12;
int** M2;
int** AUXM21;
int** M3;
int** AUXM31;
int** M4;
int** AUXM41;
int** M5;
int** AUXM51;
int** M6;
int** AUXM61;
int** AUXM62;
int** M7;
int** AUXM71;
int** AUXM72;

void getArgs(int argc, char **argv)
{
	if(argc < 4) {
		printf("Not enough paramters: ./program N NReps printLevel\nprintLevel: 0=no, 1=some, 2=verbouse\n");
		exit(1);
	}
	N = atoi(argv[1]);
	NReps = atoi(argv[2]);
	printLevel = atoi(argv[3]);
}

int ** allocMatrix(int n, int m)
{
	int ** matrix;
	matrix = malloc(sizeof(int *) * n);
	if(matrix == NULL) {
		printf("malloc failed!");
		exit(1);
	}
	int i;
	for(i = 0; i < N; i++) {
		matrix[i] = malloc(sizeof(int) * N);
		if(matrix[i] == NULL) {
			printf("malloc failed!");
			exit(1);
		}
	}
	return(matrix);
}

void init()
{
	int i, j;
	a = allocMatrix(N, N);
	b = allocMatrix(N, N);
	c = allocMatrix(N, N);
	M1 = allocMatrix(N, N);
	AUXM11 = allocMatrix(N, N);
	AUXM12 = allocMatrix(N, N);
	M2 = allocMatrix(N, N);
	AUXM21 = allocMatrix(N, N);
	M3 = allocMatrix(N, N);
	AUXM31 = allocMatrix(N, N);
	M4 = allocMatrix(N, N);
	AUXM41 = allocMatrix(N, N);
	M5 = allocMatrix(N, N);
	AUXM51 = allocMatrix(N, N);
	M6 = allocMatrix(N, N);
	AUXM61 = allocMatrix(N, N);
	AUXM62 = allocMatrix(N, N);
	M7 = allocMatrix(N, N);
	AUXM71 = allocMatrix(N, N);
	AUXM72 = allocMatrix(N, N);

	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			c[i][j] = 0;
			M1[i][j] = 0;
			AUXM11[i][j] = 0;
			AUXM12[i][j] = 0;
			M2[i][j] = 0;
			AUXM21[i][j] = 0;
			M3[i][j] = 0;
			AUXM31[i][j] = 0;
			M4[i][j] = 0;
			AUXM41[i][j] = 0;
			M5[i][j] = 0;
			AUXM51[i][j] = 0;
			M6[i][j] = 0;
			AUXM61[i][j] = 0;
			AUXM62[i][j] = 0;
			M7[i][j] = 0;
			AUXM71[i][j] = 0;
			AUXM72[i][j] = 0;
			if(i <= j) {
				a[i][j] = 1;
				b[i][j] = 1;
			}
			else {
				a[i][j] = 0;
				b[i][j] = 0;
			}
		}
	}
}

void printAll()
{
	int i, j;
	for(i = 0; i < N; i++) {
		for(j = 0; j < N; j++) {
			printf("%i\t",c[i][j]);
		}
		printf("\n");
	}
}

void printPartial()
{
	printAll();
}

void print()
{
	if(printLevel == 0)
		return;
	else if(printLevel == 1)
		printPartial();
	else
		printAll();
}

void mulMatrix(int** C,  int startCi, int startCj, int** A, int startAi, int startAj, int** B, int startBi, int startBj)
{
	// Do not parallelize me
	int i, j, k;
	for(i = 0; i < N/2; i++)
		for(j = 0; j < N/2; j++)
			for(k = 0; k < N/2; k++)
				C[startCi + i][startCj + j] += A[startAi + i][startAj + k] * B[startBi + k][startBj + j];
}

void addMatrix(int** C, int startCi, int startCj, int** A, int startAi, int startAj, int** B, int startBi, int startBj)
{
	// Do not parallelize me
	int i, j;
	for(i = 0; i < N/2; i++)
		for(j = 0; j < N/2; j++)
			C[startCi + i][startCj + j] = A[startAi + i][startAj + j] + B[startBi + i][startBj + j];
}

void subMatrix(int** C, int startCi, int startCj,  int** A, int startAi, int startAj, int** B, int startBi, int startBj)
{
	// Do not parallelize me
	int i, j;
	for(i = 0; i < N/2; i++)
		for(j = 0; j < N/2; j++)
			C[startCi + i][startCj + j] = A[startAi + i][startAj + j] - B[startBi + i][startBj + j];
}

void* threadFunction0(void *var) {
	int tid = *(int*)var;
	addMatrix(AUXM11, 0, 0, a, 0, 0, a, N/2, N/2);
	addMatrix(AUXM12, 0, 0, b, 0, 0, b, N/2, N/2);
	mulMatrix(M1, 0, 0, AUXM11, 0, 0, AUXM12, 0, 0);
}
void* threadFunction1(void *var) {
	int tid = *(int*)var;
	addMatrix(AUXM21, 0,0, a, N/2, 0, a, N/2, N/2);
	mulMatrix(M2, 0, 0, AUXM21, 0, 0, b, 0, 0);
}
void* threadFunction2(void *var) {
	int tid = *(int*)var;
	subMatrix(AUXM31, 0, 0, b, 0, N/2, b, N/2, N/2);
	mulMatrix(M3, 0, 0, a, 0, 0, AUXM31, 0, 0);
}

void* threadFunction3(void *var) {
	int tid = *(int*)var;
	subMatrix(AUXM41, 0, 0, b, N/2, 0, b, 0, 0);
	mulMatrix(M4, 0, 0, a, N/2, N/2, AUXM41, 0, 0);
}

void* threadFunction4(void *var) {
	int tid = *(int*)var;
	addMatrix(AUXM51, 0,0, a, 0, 0, a, 0, N/2);
	mulMatrix(M5, 0, 0, AUXM51, 0, 0, b, N/2, N/2);
}
void* threadFunction5(void *var) {
	int tid = *(int*)var;
	subMatrix(AUXM61, 0, 0, a, N/2, 0, a, 0, 0);
	addMatrix(AUXM62, 0, 0, b, 0, 0, b, 0, N/2);
	mulMatrix(M6, 0, 0, AUXM61, 0, 0, AUXM62, 0, 0);
}
void* threadFunction6(void *var) {
	int tid = *(int*)var;
	subMatrix(AUXM71, 0, 0, a, 0, N/2, a, N/2, N/2);
	addMatrix(AUXM72, 0, 0, b, N/2, 0, b, N/2, N/2);
	mulMatrix(M7, 0, 0, AUXM71, 0, 0, AUXM72, 0, 0);
}

void* threadFunction7(void *var) {
	int tid = *(int*)var;
	addMatrix(c, 0, 0, M1, 0, 0, M4, 0, 0);
	subMatrix(c, 0, 0, c, 0, 0, M5, 0, 0);
	addMatrix(c, 0, 0, c, 0, 0, M7, 0, 0);
}
void* threadFunction8(void *var) {
	int tid = *(int*)var;
	addMatrix(c, 0, N/2, M3, 0, 0, M5, 0, 0);
}
void* threadFunction9(void *var) {
	int tid = *(int*)var;
	addMatrix(c, N/2, 0, M2, 0, 0, M4, 0, 0);

}
void* threadFunction10(void *var) {
	int tid = *(int*)var;
	subMatrix(c, N/2, N/2, M1, 0, 0, M2, 0, 0);
	addMatrix(c, N/2, N/2, c, N/2, N/2, M3, 0, 0);
	addMatrix(c, N/2, N/2, c, N/2, N/2, M6, 0, 0);

}

int main(int argc, char *argv[])
{
	getArgs(argc, argv);
	init();

	int P = 7;
	pthread_t tid[P];
	int thread_id[P];
	for(int i = 0;i < P; i++) {
		thread_id[i] = i;
	}

	for(int i = 0; i < P; i++) {
		if (i % 7 == 0)
		pthread_create(&(tid[i]), NULL, threadFunction0, &(thread_id[i]));
		if (i % 7 == 1)
		pthread_create(&(tid[i]), NULL, threadFunction1, &(thread_id[i]));
		if (i % 7 == 2)
		pthread_create(&(tid[i]), NULL, threadFunction2, &(thread_id[i]));
		if (i % 7 == 3)
		pthread_create(&(tid[i]), NULL, threadFunction3, &(thread_id[i]));
		if (i % 7 == 4)
		pthread_create(&(tid[i]), NULL, threadFunction4, &(thread_id[i]));
		if (i % 7 == 5)
		pthread_create(&(tid[i]), NULL, threadFunction5, &(thread_id[i]));
		if (i % 7 == 6)
		pthread_create(&(tid[i]), NULL, threadFunction6, &(thread_id[i]));
	}

	for(int i = 0; i < P; i++) {
		pthread_join(tid[i], NULL);
	}
 	P = 4;
	pthread_t tid1[P];
	for(int i = 0;i < P; i++) {
		thread_id[i] = i;
	}

	for (int i = 0; i < 4; i++) {
		if (i % 4 == 0)
		pthread_create(&(tid1[i]), NULL, threadFunction7, &(thread_id[i]));

		if (i % 4 == 1)
		pthread_create(&(tid1[i]), NULL, threadFunction8, &(thread_id[i]));

		if (i % 4 == 2)
		pthread_create(&(tid1[i]), NULL, threadFunction9, &(thread_id[i]));

		if (i % 4 == 3)
		pthread_create(&(tid1[i]), NULL, threadFunction10, &(thread_id[i]));
	}


	for(int i = 0; i < P; i++) {
		pthread_join(tid1[i], NULL);
	}

	print();

	return 0;
}
