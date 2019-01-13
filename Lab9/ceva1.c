#include<mpi.h>
#include<stdio.h>
int main(int argc, char * argv[])
{
    int rank;
    int nProcesses;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);

    int a = -1;
    if (rank == 0) {
    	a = 3;
    	for (int i = 1; i < nProcesses; i ++)
    		MPI_Send(&a, 1, MPI_INT, i, 1, MPI_COMM_WORLD);
    } else {
    	MPI_Recv(&a, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    printf("Hello from %i/%i, with value a = %i\n"
        ,rank, nProcesses, a);
    MPI_Finalize();
    return 0;
}
