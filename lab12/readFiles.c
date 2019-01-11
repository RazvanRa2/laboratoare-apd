#include<string.h>
#include<stdio.h>
#include <stdlib.h>
#include<time.h>
#include<math.h>
#include <pthread.h>
/**
 * @author cristian.chilipirea
 * Create files using
 * dd if=/dev/urandom of=1.txt bs=1024 count=102400
 * dd if=/dev/urandom of=2.txt bs=1024 count=102400
 */
int n = 1024 * 1024 * 100;
char buf1[104857600];
char buf2[104857600];
void *func(void *threadid) {
	int tid = (int) threadid;
	if (tid == 1) {
		FILE *f = fopen("3.txt", "rb");
		fread(buf1, sizeof(char), n, f);
		fclose(f);
	} else {
		FILE *g = fopen("4.txt", "rb");
		fread(buf2, sizeof(char), n, g);
		fclose(g);
	}
}


int main(int argc, char * argv[]) {

	pthread_t threads[atoi(argv[1])];

	if (atoi(argv[1]) > 1) {
		for (int i = 0; i < atoi(argv[1]); i++) {
			int rc = pthread_create(&threads[i], NULL, func, (void *) i);
		}
	} else {
		FILE * f = fopen("1.txt","rb");
		FILE * g = fopen("2.txt","rb");
		clock_t begin = clock();

		fread(buf1,sizeof(char),n,f);
		fread(buf2,sizeof(char),n,g);
		fclose(f);
		fclose(g);
	}
	//clock_t end = clock();
	//double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	//printf("%f\n",time_spent);

	return 0;
}