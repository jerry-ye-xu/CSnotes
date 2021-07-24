#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <math.h>

void resize_nn(
    int* pixels_in, size_t in_width, size_t in_height,
    int* pixels_out, size_t out_width, size_t out_height
) {
    size_t x;
    size_t y;
    double adj_x;
    double adj_y;
    double x_ratio;
    double y_ratio;
    size_t out_size;
    size_t in_size_adj;

    if (
        pixels_in && pixels_out &&
        out_width && out_height &&
        in_width && in_height
    ) {
        x_ratio = in_width / (double) out_width;
        y_ratio = in_height / (double) out_height;

        for (y = 0; y < out_height; y++) {
            for (x = 0; x < out_width; x++) {
                adj_x = floor(x * x_ratio);
                adj_y = floor(y * y_ratio);

                out_size = (y * out_width) + x;
                in_size_adj = (size_t) ((adj_y * in_width) + adj_x);

                pixels_out[out_size] = pixels_in[in_size_adj];
            }
        }
    }
}

void print_bitmap(int* bitmap, size_t nrows, size_t ncols) {
    size_t idx;
    size_t x;
    size_t y;
    for (y = 0; y < nrows; y++) {
        for (x = 0; x < ncols; x++) {
            idx = (size_t) y * nrows + x;
            printf("%d", bitmap[idx]);
        }
        printf("\n");
    }
}

void test_function() {
    size_t idx;
    size_t x;
    size_t y;
    size_t nrows = 8;
    size_t ncols = 16;
    size_t nrows_resized = 4;
    size_t ncols_resized = 8;
    int* original_bitmap = malloc(sizeof(int) * nrows_resized * ncols_resized);
    int* resized_bitmap = malloc(sizeof(int) * nrows_resized * ncols_resized);

        for (y = 0; y < nrows; y++) {
            for (x = 0; x < ncols; x++) {
                idx = (size_t) y * nrows + x;

                if (x < 2) { original_bitmap[idx] = 0; }
                else if (x >= 2 && x < 6) { original_bitmap[idx] = 1; }
                else if (x >= 6 && x < 10) { original_bitmap[idx] = 0; }
                else if (x >= 10 && x < 14) { original_bitmap[idx] = 1; }
                else { original_bitmap[idx] = 0; }
            }
        }
    print_bitmap(original_bitmap, nrows, ncols);
    resize_nn(
        original_bitmap, ncols, nrows,
        resized_bitmap, ncols_resized, nrows_resized
    );
    print_bitmap(resized_bitmap, nrows_resized, ncols_resized);
    free(original_bitmap);
    free(resized_bitmap);
    original_bitmap = NULL;
    resized_bitmap = NULL;
}

int* read_bitmap(char *file_path, size_t nrows, size_t ncols) {
    int x, y, idx;
    int* bitmap;
    char letter[2];

    FILE *fp = fopen(file_path, "r");

    bitmap = malloc(sizeof(int) * nrows * ncols);
    for (y = 0; y < nrows; y++) {
        for (x = 0; x < ncols; x++) {
            if (fgets(letter, sizeof(letter), fp) != NULL) {
                if (letter[0] != '\n') {
                    idx = (size_t) y * nrows + x;
                    bitmap[idx] = atoi(&letter[0]);
                } else {
                    x--;
                }
            }
        }
    }
    return bitmap;
}

int main(int argc, char** argv) {
    char* file_path;
    size_t nrows, ncols, nrows_resized, ncols_resized;
    int* original_bitmap; int* resized_bitmap;

    if (argc != 6) { perror("Need 3 arguments for program."); exit(EXIT_FAILURE); }

    file_path = argv[1];
    nrows = (size_t) atoi(argv[2]);
    ncols = (size_t) atoi(argv[3]);
    nrows_resized = (size_t) atoi(argv[4]);
    ncols_resized = (size_t) atoi(argv[5]);

    original_bitmap = malloc(sizeof(int) * nrows_resized * ncols_resized);
    resized_bitmap = malloc(sizeof(int) * nrows_resized * ncols_resized);
    original_bitmap = read_bitmap(file_path, nrows, ncols);
    resize_nn(
        original_bitmap, ncols, nrows,
        resized_bitmap, ncols_resized, nrows_resized
    );
}
