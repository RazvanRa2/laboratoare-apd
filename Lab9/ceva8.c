#include<mpi.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
int main(int argc, char * argv[])
{
    int noPoints = 1000000;
    srand(time(NULL));
    int rank;
    int nProcesses;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);
    MPI_Status stat1, stat2;
    int s1 = 0, s2 = 0, s3 = 0, s4 = 0;
    double pai = 0;
    int no;    
        no = 0;
        for (int i = 0; i < noPoints; i ++) {
            double x, y;
            x = (float)(rand() % 1000) / 1000;
            y = (float)(rand() % 1000) / 1000;
            //printf("x is %f, y is %f\n", x, y);
            double dist = sqrt(x * x + y * y);
            if (dist < 1)
                no ++;
        }
        MPI_Send(&no, 1, MPI_INT, 0, 20, MPI_COMM_WORLD);
     if (rank == 0) {
      	MPI_Recv(&s1, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &stat1);
        MPI_Recv(&s2, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &stat2);
        MPI_Recv(&s3, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &stat2);
        MPI_Recv(&s4, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &stat2);
        pai = (4 * (float)(s1 + s2 + s3 + s4) / (4 * noPoints));
     } 
    if (rank == 0)
        printf("I am proc %i/%i\nI calculated PI as being %f\n", rank, nProcesses, pai);
    else
        printf("I am proc %i/%i\nI generated %i points and %i were inside the circle\n",
                rank, nProcesses, noPoints, no);
    MPI_Finalize();
    return 0;
}
