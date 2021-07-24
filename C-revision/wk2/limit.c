#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_until_eol(FILE *fp, int loc) {
    char chunk[128];
    char *line = malloc(sizeof(chunk));

    if (line == NULL) {
        perror("Error allocating memory.");
        exit(1);
    }
    // printf("Testing\n");
    size_t total_size = sizeof(chunk);
    // printf("total_size: %zu\n", total_size);
    while(fgets(chunk, sizeof(chunk), fp) != NULL) {
        // printf("Testing\n");
        size_t line_size = strlen(line);
        size_t chunk_size = strlen(chunk);
        if (total_size - line_size < chunk_size) {
            line = realloc(line, total_size*2);
            if(line == NULL) {
                perror("Error allocating memory.");
                free(line);
                exit(1); 
            }
        }
        // printf("Testing\n");
        strncpy(line + line_size, chunk, total_size - line_size);
        // printf("line: %s\n", line);
        line_size += chunk_size;

        // printf("Testing\n");
        // printf("line_size: %zu\n", line_size);
        // printf("line[line_size - 1]: %c\n", line[line_size - 1]);
        // printf("line[line_size]: %c\n", line[line_size]);
        if ((line[line_size] == '\n') || (line[line_size] == '\0')) {
            fprintf(stdout, "LINE\n");
            fputs(line, stdout);
            fputs("\n", stdout);
            line[0] = '\0';
            break;
        }
    }
    fseek(fp, loc, SEEK_END);
}

void read_backwards(FILE *fp, int nlines) {
    int i = -1;
    int nread = 0;
    int reached_start = 0;
    char c[2];
    char chunk[128];
    // printf("sizeof(chunk): %lu\n", sizeof(chunk));

    char *line = malloc(sizeof(chunk));
    fseek(fp, -1, SEEK_END);
    // printf("Reached here\n");
    // fgets is the one that reads until n-1 space and appends the null string
    while (fgets(c, sizeof(c), fp) != NULL) {
        // printf("ftell(fp): %ld\n", ftell(fp));
        if (ftell(fp) == 0) { reached_start = 1; }
        if ((c[0] == '\n') || ftell(fp) == 0) {
            // printf("Found end of line.\n");
            read_until_eol(fp, i);
            // exit(0);
            nread++;
            if (reached_start || nlines == nread) { exit(0); }
        }
        fseek(fp, i, SEEK_END);
        i--;
    // } else {
    //     printf("Error\n");
    }
    // printf("Hello?\n");
}

void read_forwards(FILE*fp, int nlines) {
    int nread = 0;
    
    char chunk[128];
    size_t len = sizeof(chunk);
    char *line = malloc(len);
    if (line == NULL) {
        perror("Error allocating memory.");
        exit(1);
    }
    line[0] = '\0';
    while(fgets(chunk, sizeof(chunk), fp) != NULL && nread < nlines) {
        size_t len_used = strlen(line);
        size_t chunk_used = strlen(chunk);
        if (len - len_used < chunk_used) {
            len *= 2;
            line = realloc(line, len);
            if(line == NULL) {
                perror("Error allocating memory.");
                free(line);
                exit(1); 
            }
        }
        strncpy(line + len_used, chunk, len - len_used);
        len_used += chunk_used;

        if (line[len_used - 1] == '\n') {
            fprintf(stdout, "LINE %d\n", nread);
            fputs(line, stdout);
            // fputs("\n", stdout);
            line[0] = '\0';
            nread++;           
        }
    }
}

int main(int argc, char** argv) {
    char* loc = argv[1];
    int nlines = atoi(argv[2]);
    char* file_path = argv[3];

    printf("loc: %s\n", loc);

    FILE *fp = fopen(file_path, "r");
    // printf("SEEK_SET: %d\n", SEEK_SET);
    // printf("SEEK_CUR: %d\n", SEEK_CUR);
    // printf("SEEK_END: %d\n", SEEK_END);
    // read_forwards(fp, nlines);
    read_backwards(fp, nlines);

}
