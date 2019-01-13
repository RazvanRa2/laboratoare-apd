#include<mpi.h>
#include<stdio.h>
int main(int argc, char * argv[])
{
    int rank;
    int nProcesses;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);
    MPI_Status stat1, stat2;
    int a = -1;
    if (rank == 0) {
      	MPI_Recv(&a, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &stat1);
        MPI_Recv(&a, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &stat2);

    } else {
    	a = 3;
         for (int i = 22; i < 40; i ++)
            MPI_Send(&a, 1, MPI_INT, 0, i, MPI_COMM_WORLD);
    }
    if (rank == 0)
        printf("Hello from %i, %i, with value a = %i, recieved from src %i, with tag %i, and second src %i and second tag %i\n",
                rank, nProcesses, a, stat1.MPI_SOURCE, stat1.MPI_TAG, stat2.MPI_SOURCE, stat2.MPI_TAG);
    else
    printf("Hello from %i/%i, with value a = %i\n"
        ,rank, nProcesses, a);
    MPI_Finalize();
    return 0;
}
