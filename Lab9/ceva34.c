#include<mpi.h>
#include<stdio.h>
int main(int argc, char * argv[])
{
    int rank;
    int nProcesses;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);

    int a[100];
    for (int i = 0; i < 10; i ++)
        a[i] = -1;
    if (rank == 0) {
    	for (int i = 0; i < 10; i ++)
            a[i] = i;
    } 
    MPI_Bcast(&a, 10, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Hello from %i/%i\n"
        ,rank, nProcesses, a);
    for (int i = 0; i < 10; i ++)
        printf("Hello from %i/%i, val is %i\n"
        ,rank, nProcesses, a[i]);

    MPI_Finalize();
    return 0;
}
