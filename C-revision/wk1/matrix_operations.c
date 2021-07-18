#include <stdio.h>
#include <stdlib.h>

int** construct_matrix(int nrows, int ncols) {
    int i, j;
    int val = 1;

    int** matrix = malloc(nrows * sizeof(*matrix));
    for (i = 0; i < nrows; i++) {
        matrix[i] = malloc(ncols * sizeof(**matrix));
        for (j = 0; j < ncols; j++) {
            matrix[i][j] = val;
            val++;
        }
    }

    return matrix;
}

void print_matrix(int** matrix, int nrows, int ncols) {
    int i, j;
    for (i = 0; i < nrows; i++) {
        for (j = 0; j < ncols; j++) {
            if (matrix[i][j] < 10) {
                printf(" %d ", matrix[i][j]);
            } else {
                printf("%d ", matrix[i][j]);
            }
        }
        printf("\n");
    }
}

void horizontal_flip(int** matrix, int nrows, int ncols) {
    int i, j;
    int l_tmp, r_tmp;
    int middle = (int) ncols / 2;

    for (j = 0; j < middle; j++) {
        for (i = 0; i < nrows; i++) {
            l_tmp = matrix[i][j];
            r_tmp = matrix[i][ncols-j-1];
            matrix[i][j] = r_tmp;
            matrix[i][ncols-j-1] = l_tmp;
        }
    } 
}

void vertical_flip(int** matrix, int nrows, int ncols) {
    int i, j;
    int t_tmp, b_tmp;
    int middle = (int) nrows / 2;

    for (i = 0; i < middle; i++) {
        for (j = 0; j < ncols; j++) {
            t_tmp = matrix[i][j];
            b_tmp = matrix[nrows-i-1][j];
            matrix[i][j] = b_tmp;
            matrix[nrows-i-1][j] = t_tmp;
        }
    }
}

void reverse(int** matrix, int nrows, int ncols) {
    int i, j;
    int m_col, m_row;
    int t_tmp, b_tmp;

    // int max_val = matrix[nrows-1][ncols-1];
    // int middle = (int) max_val / 2;
    m_row = (int) nrows / 2;
    m_col = (int) ncols / 2;

    for (i = 0; i < m_row; i++) {
        for (j = 0; j < ncols; j++) {
            t_tmp = matrix[i][j];
            b_tmp = matrix[nrows-i-1][ncols-1-j];
            matrix[i][j] = b_tmp;
            matrix[nrows-i-1][ncols-1-j] = t_tmp;
        }
    }

    // If there is an odd number of rows we iterate
    // through half of the middle row only.
    if (nrows % 2) {
        for (j = 0; j < m_col; j++) {
            t_tmp = matrix[i][j];
            b_tmp = matrix[i][ncols-1-j];
            matrix[i][j] = t_tmp;
            matrix[i][ncols-j-1] = b_tmp;
        }
    }
}

void odd_row_horizontal(int nrows, int ncols) {
    int **matrix;
    matrix = construct_matrix(nrows, ncols); 
    horizontal_flip(matrix, nrows, ncols);
    print_matrix(matrix, nrows, ncols);
    printf("\n\n-----------\n\n");
}

void odd_row_vertical(int nrows, int ncols) {
    int **matrix;
    matrix = construct_matrix(nrows, ncols); 
    vertical_flip(matrix, nrows, ncols);
    print_matrix(matrix, nrows, ncols);
    printf("\n\n-----------\n\n");
}

void odd_row_reverse(int nrows, int ncols) {
    int **matrix;
    matrix = construct_matrix(nrows, ncols); 
    reverse(matrix, nrows, ncols);
    print_matrix(matrix, nrows, ncols);
    printf("\n\n-----------\n\n");
}

void even_row_horizontal(int nrows, int ncols) {
    int **matrix;
    matrix = construct_matrix(nrows, ncols); 
    horizontal_flip(matrix, nrows, ncols);
    print_matrix(matrix, nrows, ncols);
    printf("\n\n-----------\n\n");
}

void even_row_vertical(int nrows, int ncols) {
    int **matrix;
    matrix = construct_matrix(nrows, ncols); 
    vertical_flip(matrix, nrows, ncols);
    print_matrix(matrix, nrows, ncols);
    printf("\n\n-----------\n\n");
}

void even_row_reverse(int nrows, int ncols) {
    int **matrix;
    matrix = construct_matrix(nrows, ncols); 
    reverse(matrix, nrows, ncols);
    print_matrix(matrix, nrows, ncols);
    printf("\n\n-----------\n\n");
}


int main(int argc, char** argv) {
    int nrows, ncols;

    nrows = 7;
    ncols = 7;
    odd_row_horizontal(nrows, ncols);
    odd_row_vertical(nrows, ncols);
    odd_row_reverse(nrows, ncols);

    printf("\n\n-----------\n-----------\n\n");
    printf("\n\n-----------\n-----------\n\n");
    printf("\n\n-----------\n-----------\n\n");

    nrows = 4;
    ncols = 4;
    even_row_horizontal(nrows, ncols);
    even_row_vertical(nrows, ncols);
    even_row_reverse(nrows, ncols);
}
