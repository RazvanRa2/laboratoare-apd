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
    	for (int i = 0; i < nProcesses; i ++)
    		MPI_Send(&a, 10, MPI_INT, i, 1, MPI_COMM_WORLD);
    } else {
    	MPI_Recv(&a, 10, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    printf("Hello from %i/%i\n"
        ,rank, nProcesses, a);
    for (int i = 0; i < 10; i ++)
        printf("Hello from %i/%i, val is %i\n"
        ,rank, nProcesses, a[i]);

    MPI_Finalize();
    return 0;
}
