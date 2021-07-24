#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    int i;
    int nfiles = argc - 1;
    printf("nfiles: %d\n", nfiles);

    FILE *fp;
    FILE **fp_arr;
    for (i = 0; i < nfiles; i++) {
        printf("argv[%d]: %s\n", i+1, argv[i+1]);
        // printf("sizeof(fp): %lu", sizeof(fp));
        fp = fopen(argv[i+1], "r");
        printf("sizeof(fp): %lu\n", sizeof(fp));
        fp_arr = &fp;
        // (fp_arr+i) = &fp;
        // *(fp_arr+sizeof(fp)*i) = fp;
    }

    char chunk[5];
    // fgets(chunk, sizeof(chunk), fp);
    fgets(chunk, sizeof(chunk), fp_arr[0]);
    printf("chunk: %s\n", chunk);
    // fgets(chunk, sizeof(chunk), fp_arr[1]);
    // printf("chunk: %s\n", chunk);

    // char* file_path = argv[1];
    // FILE *fp = fopen(file_path, "r");

}
