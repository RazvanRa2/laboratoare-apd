#include<string.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<omp.h>
/**
 * @author cristian.chilipirea
 * 
 */

int n1GB = 1024*1024*1024;
char v[1024*1024*1024];

int main(int argc, char * argv[]) {
	int c;
	memset(v, '1', n1GB);

	int i;
	omp_set_num_threads(atoi(argv[1]));
	#pragma omp parallel for
	for(i=0;i<32;i++)
		memset(v+(i*32*1024*1024), '1', 32*1024*1024);


	return 0;
}