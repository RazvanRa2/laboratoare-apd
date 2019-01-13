#include<mpi.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<math.h>
int main(int argc, char * argv[])
{
    long long noPoints = 10000000000;
    srand(time(NULL));
    int rank;
    int nProcesses;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);
    MPI_Status stat1, stat2;
    long s1 = 0, s2 = 0, s3 = 0, s4 = 0;
    double pai = 0;
    int no;    
        no = 0;
        for (long long i = 0; i < noPoints / nProcesses; i ++) {
            double x, y;
            x = (float)(rand() % 2000) / 1000;
            y = (float)(rand() % 2000) / 1000;
            //printf("x is %f, y is %f\n", x, y);
            double dist = sqrt((x - 1) *( x - 1) +( y - 1) *( y - 1));
            if (dist < 1)
                no ++;
        }
        MPI_Send(&no, 1, MPI_LONG, 0, 20, MPI_COMM_WORLD);
     if (rank == 0) {
         int sum = 0;
         for (int i = 0; i < nProcesses; i ++)
         { MPI_Recv(&s1, 1, MPI_LONG, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &stat1);
            sum += s1;
         }
        
         pai = (4 *   (float)(sum) / ( noPoints));
     } 
    if (rank == 0)
        printf("I am proc %i/%i\nI calculated PI as being %f\n", rank, nProcesses, pai);
    else
        printf("I am proc %i/%i\nI generated %i points and %i were inside the circle\n",
                rank, nProcesses, noPoints, no);
    MPI_Finalize();
    return 0;
}
