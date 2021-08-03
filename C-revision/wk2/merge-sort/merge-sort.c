#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int swap(int* ptr, int i, int j) {
    int x = ptr[i];
    int y = ptr[j];
    ptr[i] = y;
    ptr[j] = x;

}

int asc(int x, int y) {
    return x > y ? 1 : 0;
}

int desc(int x, int y) {
    return x < y ? 1 : 0;
}

void merge_sort_num(int* ptr, int (*compare)(int, int), size_t size) {
    printf("*ptr: %p", (void *) ptr);
    ptr[0] = 15;
    for (int i = 0; i < size; i++) {
        printf("*ptr[%d]: %d\n", i, ptr[i]);
    }
    if(compare(ptr[0], ptr[1])) {
        swap(ptr, 0, 1);
    }
    printf("*ptr[%d]: %d\n", 0, ptr[0]);
    printf("*ptr[%d]: %d\n", 1, ptr[1]);
    // int** nums = arr;
    // for (int i = 0; i < size; i++) {
    //     printf("nums[%d]: %d", i, *nums[i]);
    // }

}

int main(int argc, char** argv) {
    // First, parse the args.
    char* file = argv[1];
    char* order = argv[2];
    char* data_type = argv[3];

    size_t nlines = 0;
    size_t size_sum = 0;
    size_t size = 25;
    char word[size];
    FILE *fp = fopen(file, "r");

    // Figure out how many lines we have then allocate required memory for it
    while (fgets(word, size, fp) != NULL) {
        // printf("word: %s\n", word);
        // printf("nlines: %lu\n", nlines);
        // printf("size: %ld\n", strlen(word));
        size_sum += strlen(word);
        nlines++;
    }
    if (fseek(fp, 0, SEEK_SET)) { exit(EXIT_FAILURE); }

    // If I malloc total size of the array and do pointer arithmetic what would happen?
    /*
        char** words_arr = malloc(sizeof(char) * size_sum);
        for (int i = 0; i < nlines; i++) {
            if (fgets(word, size, fp) == NULL) { exit(EXIT_FAILURE); }
            words_arr[i] = word;
    */

    // This saves everything to be the same string. I wonder why?...
    if (strcmp(data_type, "-alpha") == 0) {
        char* arr[nlines];
        for (int i = 0; i < nlines; i++) {
            if (fgets(word, size, fp) == NULL) { exit(EXIT_FAILURE); }

            arr[i] = malloc(sizeof(char) * strlen(word));
            if (arr[i] == NULL) { exit(EXIT_FAILURE); }
            strcpy(arr[i], word);
            printf("arr[%d]: %s\n", i, arr[i]);
        }
    }
    else if (strcmp(data_type, "-num") == 0) {
        int arr[nlines];

        char *end_char;
        for (int i = 0; i < nlines; i++) {
            if (fgets(word, size, fp) == NULL) { exit(EXIT_FAILURE); }
            // printf("word: %s\n", word);

            arr[i] = (int) strtol(word, &end_char, 10);
            // printf("arr[i]: %d\n", arr[i]);
            // printf("%s\n", end_char);
            if ((end_char[1] != '\0') || (arr[i] == '\0')) {
                printf("Error parsing numbers. Recevied: %s\n", end_char);
                exit(EXIT_FAILURE);
            }
        }
        int* ptr = arr;
        merge_sort_num(ptr, &asc, nlines);
    }

}