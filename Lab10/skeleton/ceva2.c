
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
    int b = 0;
    int c;
    for (int step = 1; step < nProcesses; step *= 2) {
        c = a[rank];
        
        if (rank >= step) {
            printf("Receiving from %i/%i\n", rank, nProcesses);

            MPI_Recv(&b, 1, MPI_INT, rank - step, 1, MPI_COMM_WORLD, &stat);
            a[rank] += b;
        }
        if (rank < nProcesses - step) {
            MPI_Send(&c, 1, MPI_INT, rank + step, 1, MPI_COMM_WORLD);
            printf("Secnding from %i/%i\n", rank, nProcesses);

        }

        

        
    }
    //if (rank == 0)
    printf("Hello from %i/%i, with value a[rank] = %i\n"
       ,rank, nProcesses, a[rank]);
    MPI_Finalize();
    return 0;
}
