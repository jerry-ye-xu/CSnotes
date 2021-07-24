#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void filter_by_value(
    int* pixels, size_t width, size_t height,
    int pixel_threshold, int negative_val, int positive_val
) {
    size_t i, j, idx;
    for (i = 0; i < height; i++) {
        for (j = 0; j < width; j++) {
            idx = (i * width) + j;
            if(pixels[idx] >= pixel_threshold) {
                pixels[idx] = positive_val;
            } else {
                pixels[idx] = negative_val;
            }
        }
    }
}

int main(int argc, char** argv) {
    int i;
    int* data;
    size_t width, height, npixels;
    unsigned int pos_val, neg_val;

    width = 5;
    height = 15;
    npixels = width * height;
    data = malloc(npixels * sizeof(int));

    for (i = 0; i < npixels; i++) {
        data[i] = rand();
    }

    pos_val = 0xffffffff;
    neg_val = 0x22222222;

    filter_by_value(
        data, width, height,
        (pos_val - neg_val) / 2, neg_val, pos_val
    );
}
