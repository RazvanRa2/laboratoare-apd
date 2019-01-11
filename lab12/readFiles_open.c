#include<string.h>
#include<stdio.h>
#include<time.h>
#include<math.h>
#include<stdlib.h>
#include <omp.h>
/**
 * @author cristian.chilipirea
 * Create files using
 * dd if=/dev/urandom of=1.txt bs=1024 count=102400
 * dd if=/dev/urandom of=2.txt bs=1024 count=102400
 */
 
int n = 1024*1024*100;
char buf1[104857600];
char buf2[104857600];
int main(int argc, char * argv[]) {

	omp_set_num_threads(atoi(argv[1]));
	#pragma omp parallel 
	{

		#pragma omp sections 
		{

			#pragma omp section 
			{
				FILE *f = fopen("1.txt", "rb");
				fread(buf1, sizeof(char), n, f);
				fclose(f);
			}

			#pragma omp section 
			{
				FILE *g = fopen("2.txt", "rb");
				fread(buf2, sizeof(char), n, g);
				fclose(g);
			}


		}
	}
	return 0;
}