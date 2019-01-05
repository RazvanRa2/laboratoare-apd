#include <stdlib.h>
#include <stdio.h>
int **matrix;
int n, m, r;

int cmpRule (const void *a, const void *b) {
    return ( *(int*)a - *(int*)b );
}

void sortRow() {
    qsort(matrix[r - 1], m, sizeof(int), cmpRule);
}

void sortColumn() {
    int* temp = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        temp[i] = matrix[i][r - 1];
    }
    qsort(temp, n, sizeof(int), cmpRule);
    for (int i = 0; i < n; i++) {
        matrix[i][r - 1] = temp[i];
    }
}

int main(int argc, char *argv[]){
    if(argc < 4) {
        printf("Not enough paramters: ./program N M R printLevel\nprintLevel: 0=no, 1=yes\n");
        exit(1);
    }
    n = atoi(argv[1]);
    m = atoi(argv[2]);
    r = atoi(argv[3]);
    matrix = malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++) {
        matrix[i] = malloc(sizeof(int) * m);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i % 2 == 0 && j % 2 == 1) {
                matrix[i][j] = i + j;
            } else {
                matrix[i][j] = i - j;
            }
        }
    }
    printf("Unsorted %d\n", r);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }

    sortColumn();

    printf("Sorted %d\n", r);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }


    return 0;
}
