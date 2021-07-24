#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_next_word(FILE **fp_arr, int nfiles) {
    // printf("fp...");
    int i;
    int j;
    int k;
    char chunk[2];
    char prev[2];

    // Limitation... each word must be less than 64 bytes.
    size_t char_size = 64;
    char word[char_size];    

    FILE *fp;
    int nlines = 7;

    // We introduce a hack here so that we know in advance how many rows of
    // data there will be.
    for (k = 0; k < nlines; k++) {
        for (i = 0; i < nfiles; i++) {
            j = 0;
            fp = fp_arr[i];
            while(fgets(chunk, sizeof(chunk), fp) != NULL) {
                // printf("chunk[0]: %c\n", chunk[0]);
                if (chunk[0] == ' ') {
                    if (
                        prev[0] != ' ' && 
                        prev[0] != '\0' && 
                        prev[0] != '\n'
                    ) { 
                        printf("%s ", word); 
                        memset(word, 0, char_size);
                        break;
                    }
                } else if (chunk[0] == '\n') {
                    if (
                        prev[0] != ' ' && 
                        prev[0] != '\0' && 
                        prev[0] != '\n'
                    ) { 
                        printf("%s ", word);
                        memset(word, 0, char_size);
                        break;
                    }
                }
                word[j] = chunk[0];
                prev[0] = chunk[0];
                // printf("prev[0]: %c\n", prev[0]);
                // printf("nwords: %d\n", nwords);
                j++;
            }
            if (
                // k >= nlines - 3 &&
                prev[0] != ' ' && 
                prev[0] != '\0' && 
                prev[0] != '\n'
            ) {
                printf("%s ", word);
                memset(word, 0, char_size);
            }
        }
        printf("\n");
    }
}

int main(int argc, char** argv) {
    int i;
    int nfiles = argc - 1;
    // printf("nfiles: %d\n", nfiles);

    FILE *fp;
    FILE *fp_arr[nfiles];
    for (i = 0; i < nfiles; i++) {
        // printf("argv[%d]: %s\n", i+1, argv[i+1]);
        fp = fopen(argv[i+1], "r");
        fp_arr[i] = fp;
    }

    // char chunk[5];
    // fgets(chunk, sizeof(chunk), fp);
    // fgets(chunk, sizeof(chunk), fp_arr[0]);
    // printf("chunk: %s\n", chunk);
    // fgets(chunk, sizeof(chunk), fp_arr[1]);
    // printf("chunk: %s\n", chunk);

    print_next_word(fp_arr, nfiles);

    // char* file_path = argv[1];
    // FILE *fp = fopen(file_path, "r");

}
