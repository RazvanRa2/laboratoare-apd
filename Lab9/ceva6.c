#include<mpi.h>
#include<stdio.h>
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
     	MPI_Recv(&a, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &stat);

    } else {
    	a = 3;
        MPI_Send(&a, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
    }
    if (rank == 0)
        printf("Hello from %i, %i, with value a = %i, recieved from src %i\n",
                rank, nProcesses, a, stat.MPI_SOURCE);
    else
    printf("Hello from %i/%i, with value a = %i\n"
        ,rank, nProcesses, a);
    MPI_Finalize();
    return 0;
}
