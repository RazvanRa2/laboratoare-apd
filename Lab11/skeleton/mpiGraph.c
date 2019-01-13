#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>

/**
 * @author cristian.chilipirea
 * Run: mpirun -np 12 ./a.out
 */

#define N 12

int* nodes[N];

int graph[][2] = { { 0, 1 }, { 1, 2 }, { 2, 3 },
                  { 3, 4 }, { 4, 11 }, { 11, 5 },
                  { 5, 6 }, { 6, 7 }, { 7, 8 },
                  { 8, 9 }, { 9, 10 }, { 10, 9 },
                  { 9, 8 }, { 8, 7 }, { 7, 6 },
                  { 6, 5 }, { 5, 11 }, { 11, 4 },
                  { 4, 3 }, { 3, 2 }, { 2, 1 },
                  { 1, 0 }, { 9, 5 }, { 5, 9 },
                  { 5, 3 }, { 3, 5 }, { 0, 2 },
                  { 2, 0 }, { 9, 7 }, { 7, 9 } };
/*int graph[][2] = {{0, 1}, {1, 0},
                  {1, 2}, {2, 1},
                  {1, 3}, {3, 1},
                  {2, 3}, {3, 2}};*/

int M = sizeof(graph) / sizeof(graph[0]);

int getNeighbors(int node, int** neighbors) {
    int* neighbors_aux = (int*) calloc(N, sizeof(int));
    if (neighbors_aux == NULL) {
        return 0;
    }
    int nNeighbors = 0;
    for (int i = 0; i < M; i++) {
        if (graph[i][0] == node) {
            neighbors_aux[nNeighbors++] = graph[i][1];
        }
    }
    if (nNeighbors == 0) {
        free(neighbors_aux);
        return 0;
    }
    int* aux = (int*) realloc(neighbors_aux, nNeighbors * sizeof(int));
    *neighbors = aux;
    return nNeighbors;
}

void freeNeighbors(int* neighbors) {
    if (neighbors == NULL) {
        return;
    }
    free(neighbors);
}

int main(int argc, char * argv[]) {
	int rank;
	int nProcesses;

	MPI_Init(&argc, &argv);
	MPI_Status status;
	MPI_Request request;


	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);
	//printf("Hello from %i/%i\n", rank, nProcesses);

	int* neighbors;
    int n = getNeighbors(rank, &neighbors);
    printf("%d: ", rank);
    for (int i = 0; i < n; i++) {
        printf("%d ", neighbors[i]);
    }
    printf("\n");

    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == 0) {
        printf("\n");
    }
    MPI_Barrier(MPI_COMM_WORLD);

	int topology[N];
	for (int i = 0; i < N; i++) {
        topology[i] = -1;
	}
    if (rank == 0) {
        for (int i = 0; i < n; i++) {
            MPI_Send(topology, N, MPI_INT, neighbors[i], 0, MPI_COMM_WORLD);
        }
        for (int i = 0; i < n; i++) {
            int new_topology[N];
            MPI_Recv(new_topology, N, MPI_INT, neighbors[i], 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            for (int j = 0; j < N; j++) {
                if (topology[j] == -1) {
                    topology[j] = new_topology[j];
                }
            }
        }
    } else {
        int new_topology[N];
        MPI_Recv(new_topology, N, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
        int parent = status.MPI_SOURCE;
        topology[rank] = parent;
        for (int j = 0; j < N; j++) {
            if (topology[j] == -1) {
                topology[j] = new_topology[j];
            }
        }
        for (int i = 0; i < n; i++) {
            if (neighbors[i] != parent) {
                MPI_Send(topology, N, MPI_INT, neighbors[i], 0, MPI_COMM_WORLD);
            }
        }
        for (int i = 0; i < n; i++) {
            if (neighbors[i] != parent) {
                int new_topology[N];
                MPI_Recv(new_topology, N, MPI_INT, neighbors[i], 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                for (int j = 0; j < N; j++) {
                    if (topology[j] == -1) {
                        topology[j] = new_topology[j];
                    }
                }
            }
        }
        MPI_Send(topology, N, MPI_INT, parent, 0, MPI_COMM_WORLD);
    }
    MPI_Bcast(topology, N, MPI_INT, 0, MPI_COMM_WORLD);
    printf("%d: ", rank);
    for (int i = 0; i < N; i++) {
        printf("%d ", topology[i]);
    }
    printf("\n");

    MPI_Barrier(MPI_COMM_WORLD);
    if (rank == 0) {
        printf("\n");
    }
    MPI_Barrier(MPI_COMM_WORLD);

    int msg;
    if (rank == 0) {
        // sender
        int toVisit[N] = {0};
        msg = 11;
        int node = 10;
        toVisit[node] = 1;
        while (topology[node] != rank) {
            node = topology[node];
            toVisit[node] = 1;
        }
        toVisit[rank] = 1;
        printf("I am %d, I received message %X from %d sending to %d\n",
                rank, msg, -1, node);
        MPI_Send(&msg, 1, MPI_INT, node, 0, MPI_COMM_WORLD);

        msg = 0; // send null mesage to instruct them to stay away :))
        for (int i = 0; i < N; i++) {
            if (toVisit[i] == 0) {
                MPI_Send(&msg, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            }
        }
    } else if (rank == 10) {
        // destination
        MPI_Recv(&msg, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
        printf("I am %d, I received message %X from %d sending to %d\n",
                rank, msg, status.MPI_SOURCE, -1);
    } else {
        // intermediar
        MPI_Recv(&msg, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, &status);
        if (msg != 0) {
            int node = 10;
            while (topology[node] != rank) {
                node = topology[node];
            }
            printf("I am %d, I received message %X from %d sending to %d\n",
                    rank, msg, status.MPI_SOURCE, node);
            MPI_Send(&msg, 1, MPI_INT, node, 0, MPI_COMM_WORLD);
        }
    }

    freeNeighbors(neighbors);

	//printf("Bye from %i/%i\n", rank, nProcesses);
	MPI_Finalize();
	return 0;
}
