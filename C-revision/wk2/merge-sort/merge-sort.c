#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_arr(int* ptr, size_t size) {
    for (int i = 0; i < size; i++) {
        printf("ptr[%d]: %d\n", i, ptr[i]);
    }
}

void swap(int* ptr, int i, int j) {
    int x = ptr[i];
    int y = ptr[j];
    ptr[i] = y;
    ptr[j] = x;
}

int desc(int x, int y) {
    return x > y ? 1 : 0;
}

int asc(int x, int y) {
    return x < y ? 1 : 0;
}

void merge_num(int* ptr, int (*compare)(int, int), size_t l_idx, size_t m_idx, size_t r_idx) {
    int lhs_idx = m_idx - l_idx + 1;
    int rhs_idx = r_idx - m_idx;
    int left_arr[lhs_idx];
    int right_arr[rhs_idx];

    for (int i = 0; i < lhs_idx; i++) {
        left_arr[i] = ptr[l_idx + i];
    }
    for (int i = 0; i < rhs_idx; i++) {
        right_arr[i] = ptr[1+ m_idx + i];
    }

    int l = 0;
    int r = 0;
    int k = l_idx;
    while (l < lhs_idx && r < rhs_idx) {
        if(compare(left_arr[l], right_arr[r])) {
            ptr[k] = left_arr[l];
            l++;
        } else {
            ptr[k] = right_arr[r];
            r++;
        }
        k++;
    }
    while (l < lhs_idx) {
        ptr[k] = left_arr[l];
        l++;
        k++;
    }
    while (r < rhs_idx) {
        ptr[k] = right_arr[r];
        r++;
        k++;
    }
}

void merge_sort_num(int* ptr, int (*compare)(int, int), size_t l_idx, size_t r_idx) {
    if (l_idx < r_idx) {
        // Prevents overflow
        int m_idx = (int) (l_idx + (r_idx - l_idx) / 2);
        // printf("l_idx: %d\n", l_idx);
        // printf("r_idx: %d\n", r_idx);
        // printf("m_idx: %d\n", m_idx);

        merge_sort_num(ptr, compare, l_idx, m_idx);
        merge_sort_num(ptr, compare, m_idx+1, r_idx);

        merge_num(ptr, compare, l_idx, m_idx, r_idx);
    }
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
        if (strcmp(order, "-a")) {
            merge_sort_num(ptr, &asc, 0, nlines - 1);
        } else if (strcmp(order, "-d")) {
            merge_sort_num(ptr, &desc, 0, nlines - 1);
        } else {
            exit(EXIT_FAILURE);
        }
        print_arr(ptr, nlines);
    }

}