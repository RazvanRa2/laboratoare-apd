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
    int a[16] = {9, 4, 2, 7, 3, 5, 6, 1, 2, 5, 6, 1, 3, 9, 0, 1};
    int b = a[rank];
    int c = 0;
    for (int step = 2; step <= nProcesses; step *= 2) {
        if (rank % step  == 0) {
            MPI_Recv(&c, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &stat);
            b += c;
        }
        if (rank % step == step / 2) {
            MPI_Send(&b, 1, MPI_INT, rank - step / 2, 1, MPI_COMM_WORLD);
            printf("Secnding from %i/%i\n", rank, nProcesses);

        }
    }
    if (rank == 0)
    printf("Hello from %i/%i, with value b = %i\n"
        ,rank, nProcesses, b);
    MPI_Finalize();
    return 0;
}
