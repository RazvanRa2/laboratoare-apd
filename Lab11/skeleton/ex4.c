#include<mpi.h>
#include<stdio.h>
/**
 * @author cristian.chilipirea
 * Run: mpirun -np 12 ./a.out
 */

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
int cont = 0;
int* getNeighbours(int node) {
 	int *neighbours, no = 0;
 	cont = 0;
 	for (int i = 0; i < 30; i ++) {
 		if (graph[i][0] == node)// || graph[i][1] == node)
 			no++;
 	}
 	//no /= 2;
 	neighbours = (int *)malloc(no * sizeof(int));
 	for (int i = 0; i < 30; i ++) {
 		if (graph[i][0] == node)
 			neighbours[cont++] = graph[i][1];
 	}
 	return neighbours;
}

int* getBFS(int root) {
	int *visited = (int *)malloc(12 * sizeof(int));
	int *queue = (int *)malloc(12 * 12 * sizeof(int));
	int start = 0, finish;
	for (int i = 0; i < 12; i ++) {
		visited[i] = -1;
	}
	int *neigh = getNeighbours(root);
	for (int i = 0; i < cont; i ++) {
		visited[neigh[i]] = neigh[i];
		queue[i] = neigh[i];
	}
	visited[root] = root;
	finish = cont;
	while (start <= finish) {
		int *neigh = getNeighbours(queue[start ++]);
		for (int i = 0; i < cont; i ++) {
			if (visited[neigh[i]] == -1) {
				visited[neigh[i]] = visited[queue[start - 1]];
				queue[finish ++] = neigh[i];
			}
		}
	}
	return visited;
}

void sendRank10(int rank) {
	int *neighbours = getBFS(rank);
	int a = 3;
	MPI_Status stat;
	if (rank == 0) {
		MPI_Send(&a, 1, MPI_INT, neighbours[10], 1, MPI_COMM_WORLD);
	} else {
		MPI_Recv(&a, 1, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &stat);
		printf("I am %i, I received message from %i sending through %i", rank, stat.MPI_SOURCE, neighbours[10]);
		if (rank != 10)
			MPI_Send(&a, 1, MPI_INT, neighbours[10], 1, MPI_COMM_WORLD);		
	}
}

void dst(int rank) {
	int *neigh = getNeighbours(rank);
	int parents[12],
		parentsRecv[12];
	MPI_Status stat, status;
	MPI_Request sendRequest[12], recvRequest[12], req;
	int top[100][2];
	int top_aux[100][2];
	for (int i = 0; i < 100; i ++) {
		top[i][0] = top[i][1] = top_aux[i][0] = top_aux[i][1] = 0;
	}
	int sz = 0;
	for (int i = 0; i < cont; i ++) {
		top[sz][0] = rank;
		top[sz][1] = neigh[i];
		sz ++;
		top[sz][0] = neigh[i];
		top[sz][1] = rank;
		sz ++;
	}
	int recv;
	for (int i = 0; i < 100; i ++) {
		for (int j = 0; j < cont; j ++) {
			MPI_Send(&top, 50 * 2, MPI_INT, neigh[j], 1, MPI_COMM_WORLD);
		}
		for (int j = 0; j < cont; j ++) {
			MPI_Recv(&top_aux, 50 * 2, MPI_INT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &stat);
			for (int k = 0; k < 100; k ++) {
				short found = 0;
				for (int l = 0; l < sz; l ++) {
					if (top_aux[k][0] == top[l][0] &&
						top_aux[k][1] == top[l][1]) {
						found = 1;
					}
				}
				if (found == 0) {
					top[sz][0] = top_aux[k][0];
					top[sz][1] = top_aux[k][1];
					sz ++;
				}
			}
		}
	}
	if (rank == 2) {
		for (int i = 0; i < sz; i ++) {
			printf("Node %i is neigh with %i\n", top[i][0], top[i][1]);
		}
		printf("Size is %i\n", sz);
	}
	int max = -1;
	for (int i = 0; i < sz; i ++) {
		if (top[i][0] > max)
			max = top[i][0];
	}
	printf("Maximum from rank %i is %i\n", rank, max);
}

void count(int rank) {
	int *neigh = getNeighbours(rank);
	MPI_Status stat, status;
	MPI_Request sendRequest[12], recvRequest[12], req;
	int recv;
	float cnt = 0, cntRecv;
	if (rank == 11)
		cnt = 1;
	for (int i = 0; i < 100000; i ++) {
		for (int j = 0; j < cont; j ++) {
			MPI_Send(&cnt, 1, MPI_FLOAT, neigh[j], 1, MPI_COMM_WORLD);
			MPI_Recv(&cntRecv, 1, MPI_FLOAT, MPI_ANY_SOURCE, 1, MPI_COMM_WORLD, &stat);
			cnt = (cnt + cntRecv) / 2;
		}
	}
	printf("Node %i says there are %f nodes\n", rank, 1.0f/cnt);
}


int main(int argc, char * argv[]) {
	int rank;
	int nProcesses;

	MPI_Init(&argc, &argv);
	MPI_Status status;
	MPI_Request request;


	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &nProcesses);
	printf("Hello from %i/%i\n", rank, nProcesses);
	/*int *neighbours = getNeighbours(rank);
	for (int i = 0; i < cont; i ++)
		printf("%i is neigh with %i\n", rank, neighbours[i]);
	neighbours = getBFS(rank);
	for (int i = 0; i < 12; i ++)
		printf("Fastest route from %i to %i starts in %i\n", rank, i, neighbours[i]);
	*/
	//dst(rank);
	//sendRank10(rank);
	count(rank);
	printf("Bye from %i/%i\n", rank, nProcesses);
	MPI_Finalize();
	return 0;
}