#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>
int main(int argc, char* argv[]) {

    int rank, size;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    for (long i = 0; i < 100000000 / size; i++) {
        int a = sqrt(sqrt(i)) * log(i);
    }

    MPI_Finalize();

    return 0;
}