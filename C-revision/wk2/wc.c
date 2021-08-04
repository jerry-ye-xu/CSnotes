#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    char* file_path = argv[1];
    FILE *fp = fopen(file_path, "r");

    int nchars = 0;
    int nwords = 0;
    int nlines = 0;
    char chunk[2];
    char prev[2];

    while(fgets(chunk, sizeof(chunk), fp) != NULL) {
        // printf("chunk[0]: %c\n", chunk[0]);
        if (chunk[0] == ' ') {
            if (
                prev[0] != ' ' && 
                prev[0] != '\0' && 
                prev[0] != '\n'
            ) { nwords++; }
        } else if (chunk[0] == '\n') {
            if (
                prev[0] != ' ' && 
                prev[0] != '\0' && 
                prev[0] != '\n'
            ) { nwords++; }
            nlines++;
        } else {
            nchars++;
        }
        prev[0] = chunk[0];
        // printf("prev[0]: %c\n", prev[0]);
        // printf("nwords: %d\n", nwords);
    }
    // printf("prev[0]: %c\n", prev[0]);
    if (
        prev[0] != ' ' && 
        prev[0] != '\0' && 
        prev[0] != '\n'
    ) { nwords++; }
    nlines++;

    printf("nchars: %d\n", nchars);
    printf("nwords: %d\n", nwords);
    printf("nlines: %d\n", nlines);
}
