#include "maze.h"

/*
    gcc -ansi -Wall -pedantic -o maze.out maze.c && \
    ./maze.out 1 1 3 4
*/

int** construct_matrix(int nrows, int ncols, int initial_val) {
    int i, j;

    // int **matrix = (int**) malloc(nrows * sizeof(int*));
    int **matrix = (int**) malloc(nrows * sizeof(*matrix));

    for (i = 0; i < nrows; i++) {
        matrix[i] = (int*) malloc(ncols * sizeof(**matrix));
        for (j = 0; j < ncols; j++) {
            matrix[i][j] = initial_val;
        }
    }
    return matrix;
}

void print_matrix(int **matrix, int nrows, int ncols, int sx, int sy, int dx, int dy) {
    int i; int j;

    for (i = 0; i < nrows; i++) {
        printf("|");
        for (j = 0; j < ncols; j++) {
            if (i == sx && j == sy) { printf("S|"); }
            else if (i == dx && j == dy) { printf("D|"); }
            else if (matrix[i][j]) { printf("=|"); }
            else {
                matrix[i][j] == 0 ? printf(" |") : printf("x|");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void check_values(int **matrix, int x, int y) {
    printf("matrix[%d][%d] = %d\n", x, y, matrix[x][y]);
}

int is_valid_step(int nrows, int x, int ncols, int y, int ***matrix) {
    if (x < nrows && y < ncols) { return 1; }
    if (*matrix[x][y] == -1) { return 1; }

    return 0;
}

void bfs(int **matrix, struct Node *start, struct Point *dest) {
    return;
}

int main(int argc, char** argv) {
    /*
        Assume that the destination is always "further" left
        and "further" down from the starting point.

        That is, start->x >= dest->x and start->y >= dest->y.
    */
    struct Node *start, *dest;
    int **matrix;
    int ncols = 7; int nrows = 6;

    // Assume integer input is correct
    if (argc != 5) { printf("Invalid Coordinates\n"); return -1; }
    if (atoi(argv[1]) >= ncols ||
        atoi(argv[3]) >= ncols
    ) { printf("Invalid Coordinates\n"); return -1; }
    if (atoi(argv[2]) >= nrows ||
        atoi(argv[4]) >= nrows
    ) { printf("Invalid Coordinates\n"); return -1; }

    start = (struct Node*) malloc(sizeof(struct Node));
    dest = (struct Node*) malloc(sizeof(struct Node));

    start->x = atoi(argv[1]);
    start->y = atoi(argv[2]);
    dest->x = atoi(argv[3]);
    dest->y = atoi(argv[4]);
    printf("start = (%d, %d)\n", start->x, start->y);
    printf("dest  = (%d, %d)\n", dest->x, dest->y);

    matrix = construct_matrix(nrows, ncols, 0);
    // m_ptr = &matrix;
    check_values(matrix, 1, 1);
    check_values(matrix, 3, 4);
    print_matrix(matrix, nrows, ncols, start->x, start->y, dest->x, dest->y);
    return 0;
}
