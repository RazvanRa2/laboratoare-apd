#include<mpi.h>
#include<stdio.h>
#include<math.h>
int main(int argc, char * argv[])
{
    int rank;
    int nProcesses;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);
    MPI_Status stat;
    int a = -1;
    if (rank == 0) {
        a = 7;
        for (int i = 0; i < log2(nProcesses); i ++)
            MPI_Send(&a, 1, MPI_INT, (int)pow(2, i), 1, MPI_COMM_WORLD);

    } else {
    	a = 3;
        MPI_Recv(&a, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &stat);
        for (int i = log2(rank) + 1; i < log2(nProcesses - rank); i ++)
            MPI_Send(&a, 1, MPI_INT, rank + (int)pow(2, i), 1, MPI_COMM_WORLD);
    }

    printf("Hello from %i/%i, with value a = %i\n"
        ,rank, nProcesses, a);
    MPI_Finalize();
    return 0;
}
