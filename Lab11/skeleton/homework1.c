#include<mpi.h>
#include<stdio.h>
int main(int argc, char * argv[])
{
    int rank;
    int nProcesses;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);
    MPI_Request sendRequest, recvRequest;
    MPI_Status status;
    int a[1000];
    for (int i = 0; i < 1000; i ++)
    	a[i] = -1;
    if (rank == 0) {
		for (int i = 0; i < 1000; i ++)
    		a[i] = 3;
    	for (int i = 1; i < nProcesses; i ++)
    		MPI_Isend(&a, 1000, MPI_INT, i, 1, MPI_COMM_WORLD, &sendRequest);
    	for (int i = 999; i >= 0; i --)
    		a[i]++;
    } else {
    	MPI_Irecv(&a, 1000, MPI_INT, 0, 1, MPI_COMM_WORLD, &recvRequest);
    	printf("Proc %i/%i mai face ceva pana primeste mesajul...\n", rank, nProcesses);
   		MPI_Wait(&recvRequest, &status);
    }

    printf("Hello from %i/%i, with value a = %i\n"
        ,rank, nProcesses, a[999]);
    MPI_Finalize();
    return 0;
}
