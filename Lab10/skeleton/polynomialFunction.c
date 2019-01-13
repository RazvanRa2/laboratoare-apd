#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include <math.h>

/**
 * @author cristian.chilipirea
 *
 */

int main(int argc, char * argv[]) {
	int rank;
	int nProcesses;
	MPI_Init(&argc, &argv);
    MPI_Status stat;

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);
	printf("Hello from %i/%i\n", rank, nProcesses);

	//if(rank==0) { // This code is run by a single process
		int polynomialSize;
		int n;
		int i;
		int j;
		float x;

		FILE * polFunctionFile = fopen("a1.txt","rt");
		fscanf(polFunctionFile, "%i", &polynomialSize);
		float * a = malloc(sizeof(float)*polynomialSize);
		for(i=0;i<polynomialSize;i++) {
			fscanf(polFunctionFile, "%f", a+i);
		}
		fclose(polFunctionFile);

		for(x=0; x<3; x+=1) {
			float sum = 0;
			float xPowI = pow(x, rank);
			float recv;
			if (rank != 0)
				MPI_Recv(&sum, 1, MPI_FLOAT, rank - 1, 1, MPI_COMM_WORLD, &stat);
			sum += a[rank] * xPowI;
			if (rank == nProcesses - 1)
				printf("sum is %f\n", sum);
			if (rank != nProcesses - 1)
				MPI_Send(&sum, 1, MPI_INT, rank + 1, 1, MPI_COMM_WORLD);
		}
	//}

	MPI_Finalize();
	return 0;
}