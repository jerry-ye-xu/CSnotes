#ifndef MAZE
#define MAZE
#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

int** construct_matrix(int nrows, int ncols, int initial_val);
void print_matrix(int **matrix, int nrows, int ncols, int sx, int sy, int dx, int dy);
void check_values(int **matrix, int x, int y);
int is_valid_step(int nrows, int x, int ncols, int y, int ***matrix);

#endif
