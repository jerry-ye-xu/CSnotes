#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int min_(int x, int y) {
    return x < y ? x : y;
}

int max_(int x, int y) {
    return x > y ? x : y;
}

void print_arr_num(int* ptr, size_t size) {
    for (int i = 0; i < size; i++) {
        printf("ptr[%d]: %d\n", i, ptr[i]);
    }
}

void print_arr_alpha(char** ptr, size_t size) {
    for (int i = 0; i < size; i++) {
        printf("ptr[%d]: %s\n", i, ptr[i]);
    }
}

void swap(int* ptr, int i, int j) {
    int x = ptr[i];
    int y = ptr[j];
    ptr[i] = y;
    ptr[j] = x;
}

int char_compare_asc(char* x, char* y) {
    size_t min_size = (size_t) min_((int) strlen(x), (int) strlen(y));

    for (int i =0; i < min_size; i++) {
        if (tolower(x[i]) < tolower(y[i])) {
            return 1;
        } else if (x[i] > y[i]) {
            return 0;
        }
    }
    if (strlen(x) < strlen(y)) {
        return 1;
    } else {
        return 0;
    }
}

int char_compare_desc(char* x, char* y) {
    size_t min_size = (size_t) min_(
        (int) strlen(x),
        (int) strlen(y)
    );

    for (int i = 0; i < min_size; i++) {
        if (tolower(x[i]) < tolower(y[i])) {
            return 0;
        } else if (x[i] > y[i]) {
            return 1;
        }
    }
    if (strlen(x) < strlen(y)) {
        return 0;
    } else {
        return 1;
    }
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

void merge_alpha(char* ptr[], int (*compare)(char*, char*), size_t l_idx, size_t m_idx, size_t r_idx) {
    int lhs_idx = m_idx - l_idx + 1;
    int rhs_idx = r_idx - m_idx;
    char* left_arr[lhs_idx];
    char* right_arr[rhs_idx];

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

void merge_sort_alpha(char* ptr[], int (*compare)(char*, char*), size_t l_idx, size_t r_idx) {
    if (l_idx < r_idx) {
        // Prevents overflow
        int m_idx = (int) (l_idx + (r_idx - l_idx) / 2);
        // printf("l_idx: %d\n", l_idx);
        // printf("r_idx: %d\n", r_idx);
        // printf("m_idx: %d\n", m_idx);

        merge_sort_alpha(ptr, compare, l_idx, m_idx);
        merge_sort_alpha(ptr, compare, m_idx+1, r_idx);

        merge_alpha(ptr, compare, l_idx, m_idx, r_idx);
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
        char* word_p;
        char* arr[nlines];

        for (int i = 0; i < nlines; i++) {
            if (fgets(word, size, fp) == NULL) { exit(EXIT_FAILURE); }
            // printf("strlen(word): %ld\n", strlen(word));
            if (i != nlines - 1) {
                word_p = malloc(sizeof(char) * strlen(word));
            } else {
                word_p = malloc(sizeof(char) * strlen(word) + 1);
            }

            arr[i] = malloc(sizeof(char) * strlen(word));
            if (arr[i] == NULL) { exit(EXIT_FAILURE); }

            // strlen doesn't count '\0' but we need to add it to end of str
            for (int j = 0; j < strlen(word) - 1; j++) {
                word_p[j] = word[j];
            }
            // word_p[strlen(word) - 1] = '\0';
            if (i != nlines - 1) {
                word_p[strlen(word) - 1] = '\0';
            } else {
                word_p[strlen(word) - 1] = 'n';
                word_p[strlen(word)] = '\0';
            }
            strcpy(arr[i], word_p);
            // printf("arr[%d]: %s\n", i, arr[i]);
        }

        char** ptr = arr;
        if (strcmp(order, "-a")) {
            merge_sort_alpha(ptr, &char_compare_asc, 0, nlines - 1);
        } else if (strcmp(order, "-d")) {
            merge_sort_alpha(ptr, &char_compare_desc, 0, nlines - 1);
        } else {
            exit(EXIT_FAILURE);
        }
        print_arr_alpha(ptr, nlines);

        // Free everything
        for (int i = 0; i < nlines; i++) {
            free(arr[i]);
        }
        free(word_p);
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
        print_arr_num(ptr, nlines);
    }

}