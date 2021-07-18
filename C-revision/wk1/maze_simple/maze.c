#include "maze.h"

/*
    gcc -ansi -Wall -pedantic -o maze.out maze.c && \
    ./maze.out 1 1 3 4
*/

int min_(int x, int y) {
    return x < y ? x : y;
}

int max_(int x, int y) {
    return x > y ? x : y;
}

void print_args(int argc, char** argv) {
    int i;
    for (i = 0; i < argc; i++){
        printf("[%d] = %s\n", i, argv[i]);
    }
}

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

void find_path(int **matrix, struct Node *start, struct Node *dest) {
    /*
        Since there are no obstacles, this should be fairly straight forward.

        You simply move in one direction either up or down and then the second
        direction left or right.
    */
    int i_adj;
    int i = start->x;
    int j = start->y;
    int t_x = start->x;
    int t_y = start->y;

    if (t_x < dest->x) {
        // printf("Go down\n");
        for (i = t_x+1; i <= dest->x; i++) {
            matrix[i][t_y] = 1;
        }
        i_adj = i - 1;

    } else if (t_x > dest->x) {
        // printf("Go up\n");
        for (i = t_x-1; i >= dest->x; i--) {
            matrix[i][t_y] = 1;
        }
        i_adj = i + 1;
    } else {
        i_adj = i;
    }

    if (t_y < dest->y) {
        // printf("Go left\n");
        for (j = t_y+1; j <= dest->y; j++) {
            matrix[i_adj][j] = 1;
        }
    } else if (t_y > dest->y) {
        // printf("Go right\n");
        for (j = t_y-1; j >= dest->y; j--) {
            matrix[i_adj][j] = 1;
        }
    }
}

int tute_test_case(int argc, char** argv) {
    struct Node *start, *dest;
    int **matrix;
    int ncols = 7; int nrows = 6;

    // Assume integer input is correct
    // print_args(argc, argv);
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
    // printf("start = (%d, %d)\n", start->x, start->y);
    // printf("dest  = (%d, %d)\n", dest->x, dest->y);

    matrix = construct_matrix(nrows, ncols, 0);
    // check_values(matrix, 1, 1);
    // check_values(matrix, 3, 4);
    // print_matrix(matrix, nrows, ncols, start->x, start->y, dest->x, dest->y);

    find_path(matrix, start, dest);
    print_matrix(matrix, nrows, ncols, start->x, start->y, dest->x, dest->y);

    return 0;
}

int adjacent() {
    struct Node *start, *dest;
    int **matrix;
    int ncols = 7; int nrows = 6;

    start = (struct Node*) malloc(sizeof(struct Node));
    dest = (struct Node*) malloc(sizeof(struct Node));

    start->x = 2;
    start->y = 4;
    dest->x = 3;
    dest->y = 4;

    matrix = construct_matrix(nrows, ncols, 0);
    // print_matrix(matrix, nrows, ncols, start->x, start->y, dest->x, dest->y);
    find_path(matrix, start, dest);
    print_matrix(matrix, nrows, ncols, start->x, start->y, dest->x, dest->y);

    return 0;
}

int same_row() {
    struct Node *start, *dest;
    int **matrix;
    int ncols = 7; int nrows = 6;

    start = (struct Node*) malloc(sizeof(struct Node));
    dest = (struct Node*) malloc(sizeof(struct Node));

    start->x = 0;
    start->y = 1;
    dest->x = 0;
    dest->y = 4;

    matrix = construct_matrix(nrows, ncols, 0);
    // print_matrix(matrix, nrows, ncols, start->x, start->y, dest->x, dest->y);
    find_path(matrix, start, dest);
    print_matrix(matrix, nrows, ncols, start->x, start->y, dest->x, dest->y);

    return 0;
}

int same_col() {
    struct Node *start, *dest;
    int **matrix;
    int ncols = 7; int nrows = 6;

    start = (struct Node*) malloc(sizeof(struct Node));
    dest = (struct Node*) malloc(sizeof(struct Node));

    start->x = 1;
    start->y = 0;
    dest->x = 3;
    dest->y = 0;

    matrix = construct_matrix(nrows, ncols, 0);
    // print_matrix(matrix, nrows, ncols, start->x, start->y, dest->x, dest->y);
    find_path(matrix, start, dest);
    print_matrix(matrix, nrows, ncols, start->x, start->y, dest->x, dest->y);

    return 0;
}

int same_row_end() {
    struct Node *start, *dest;
    int **matrix;
    int ncols = 7; int nrows = 6;

    start = (struct Node*) malloc(sizeof(struct Node));
    dest = (struct Node*) malloc(sizeof(struct Node));

    start->x = 5;
    start->y = 1;
    dest->x = 5;
    dest->y = 6;

    matrix = construct_matrix(nrows, ncols, 0);
    // print_matrix(matrix, nrows, ncols, start->x, start->y, dest->x, dest->y);
    find_path(matrix, start, dest);
    print_matrix(matrix, nrows, ncols, start->x, start->y, dest->x, dest->y);

    return 0;
}

int same_col_end() {
    struct Node *start, *dest;
    int **matrix;
    int ncols = 7; int nrows = 6;

    start = (struct Node*) malloc(sizeof(struct Node));
    dest = (struct Node*) malloc(sizeof(struct Node));

    start->x = 0;
    start->y = 6;
    dest->x = 4;
    dest->y = 6;

    matrix = construct_matrix(nrows, ncols, 0);
    // print_matrix(matrix, nrows, ncols, start->x, start->y, dest->x, dest->y);
    find_path(matrix, start, dest);
    print_matrix(matrix, nrows, ncols, start->x, start->y, dest->x, dest->y);

    return 0;
}

int right_then_up() {
    struct Node *start, *dest;
    int **matrix;
    int ncols = 7; int nrows = 6;

    start = (struct Node*) malloc(sizeof(struct Node));
    dest = (struct Node*) malloc(sizeof(struct Node));

    start->x = 3;
    start->y = 1;
    dest->x = 1;
    dest->y = 5;

    matrix = construct_matrix(nrows, ncols, 0);
    // print_matrix(matrix, nrows, ncols, start->x, start->y, dest->x, dest->y);
    find_path(matrix, start, dest);
    print_matrix(matrix, nrows, ncols, start->x, start->y, dest->x, dest->y);

    return 0;
}

int left_then_up() {
    struct Node *start, *dest;
    int **matrix;
    int ncols = 7; int nrows = 6;

    start = (struct Node*) malloc(sizeof(struct Node));
    dest = (struct Node*) malloc(sizeof(struct Node));

    start->x = 4;
    start->y = 4;
    dest->x = 1;
    dest->y = 2;

    matrix = construct_matrix(nrows, ncols, 0);
    // print_matrix(matrix, nrows, ncols, start->x, start->y, dest->x, dest->y);
    find_path(matrix, start, dest);
    print_matrix(matrix, nrows, ncols, start->x, start->y, dest->x, dest->y);

    return 0;
}

int right_then_down() {
    struct Node *start, *dest;
    int **matrix;
    int ncols = 7; int nrows = 6;

    start = (struct Node*) malloc(sizeof(struct Node));
    dest = (struct Node*) malloc(sizeof(struct Node));

    start->x = 1;
    start->y = 1;
    dest->x = 4;
    dest->y = 5;

    matrix = construct_matrix(nrows, ncols, 0);
    // print_matrix(matrix, nrows, ncols, start->x, start->y, dest->x, dest->y);
    find_path(matrix, start, dest);
    print_matrix(matrix, nrows, ncols, start->x, start->y, dest->x, dest->y);

    return 0;
}

int left_then_down() {
    struct Node *start, *dest;
    int **matrix;
    int ncols = 7; int nrows = 6;

    start = (struct Node*) malloc(sizeof(struct Node));
    dest = (struct Node*) malloc(sizeof(struct Node));

    start->x = 1;
    start->y = 4;
    dest->x = 5;
    dest->y = 2;

    matrix = construct_matrix(nrows, ncols, 0);
    // print_matrix(matrix, nrows, ncols, start->x, start->y, dest->x, dest->y);
    find_path(matrix, start, dest);
    print_matrix(matrix, nrows, ncols, start->x, start->y, dest->x, dest->y);

    return 0;
}

int top_left_to_bottom_right() {
    struct Node *start, *dest;
    int **matrix;
    int ncols = 7; int nrows = 6;

    start = (struct Node*) malloc(sizeof(struct Node));
    dest = (struct Node*) malloc(sizeof(struct Node));

    start->x = 0;
    start->y = 0;
    dest->x = 5;
    dest->y = 6;

    matrix = construct_matrix(nrows, ncols, 0);
    // print_matrix(matrix, nrows, ncols, start->x, start->y, dest->x, dest->y);
    find_path(matrix, start, dest);
    print_matrix(matrix, nrows, ncols, start->x, start->y, dest->x, dest->y);

    return 0; 
}

int bottom_left_to_top_right() {
    struct Node *start, *dest;
    int **matrix;
    int ncols = 7; int nrows = 6;

    start = (struct Node*) malloc(sizeof(struct Node));
    dest = (struct Node*) malloc(sizeof(struct Node));

    start->x = 5;
    start->y = 0;
    dest->x = 0;
    dest->y = 6;

    matrix = construct_matrix(nrows, ncols, 0);
    // print_matrix(matrix, nrows, ncols, start->x, start->y, dest->x, dest->y);
    find_path(matrix, start, dest);
    print_matrix(matrix, nrows, ncols, start->x, start->y, dest->x, dest->y);

    return 0; 
}


int main(int argc, char** argv) {
    int res;
    res = tute_test_case(argc, argv);
    res = adjacent();
    res = same_row();
    res = same_col();
    res = same_row_end();
    res = same_col_end();
    res = right_then_up();
    res = left_then_up();
    res = right_then_down();
    res = left_then_down();
    res = top_left_to_bottom_right();
    res = bottom_left_to_top_right();
    return max_(res, 0);
}
