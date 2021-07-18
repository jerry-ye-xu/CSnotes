#include <stdio.h>

void reverse_array(int* arr, int size) {
    int i;
    int j;
    int h_val;
    int t_val;

    int m_idx = (int) size / 2;

    for (i = 0; i < m_idx; i++) {
        h_val = arr[i];
        t_val = arr[size - 1 - i];
        // printf("i=%d\n", i);
        // printf("h_val: %d\n", h_val);
        // printf("t_val: %d\n", t_val);

        arr[i] = t_val;
        arr[size - 1 - i] = h_val;
    }
}

void print_arr(int* arr, int size) {
    int i;
    printf("arr: ");
    for (i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(int args, char** argv) {
    int arr[] = {1};
    int arr2[] = {1, 2, 3, 4, 5, 6, 7};
    int arr3[] = {1, 2, 3, 4, 5, 6, 7, 8};
    print_arr(arr, 1);
    print_arr(arr2, 7);
    print_arr(arr3, 8);

    reverse_array(arr, 1);
    reverse_array(arr2, 7);
    reverse_array(arr3, 8);

    print_arr(arr, 1);
    print_arr(arr2, 7);
    print_arr(arr3, 8);

}