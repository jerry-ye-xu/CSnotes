#include <stdio.h>
#include <stdlib.h>

void print_arr(int* arr, int size) {
    int i;
    printf("arr: ");
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int* spiral(int* arr, int size) {
    int i;
    int d;
    int tmp;
    int sp_idx = (int) (size-1) / 2;
    int* sp_arr = (int*) malloc(size * sizeof(int));

    for (i = 0; i < size; i++) {
        if (i % 2 == 0) {
            sp_idx -= i;
        } else {
            sp_idx += i;
        }
        sp_arr[sp_idx] = arr[i];
    }

    return sp_arr;
}

int main(int argc, char **argv) {
    int arr1[] = {1};
    int arr2[] = {1, 2, 3, 4, 5, 6, 7};
    int arr3[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int arr4[] = {1, 2};
    int arr5[] = {1, 2, 3};

    print_arr(arr1, 1);
    print_arr(arr2, 7);
    print_arr(arr3, 8);
    print_arr(arr4, 2);
    print_arr(arr5, 3);

    int* sp_arr1 = spiral(arr1, 1);
    int* sp_arr2 = spiral(arr2, 7);
    int* sp_arr3 = spiral(arr3, 8);
    int* sp_arr4 = spiral(arr4, 2);
    int* sp_arr5 = spiral(arr5, 3);
    print_arr(sp_arr1, 1);
    print_arr(sp_arr2, 7);
    print_arr(sp_arr3, 8);
    print_arr(sp_arr4, 2);
    print_arr(sp_arr5, 3);
}