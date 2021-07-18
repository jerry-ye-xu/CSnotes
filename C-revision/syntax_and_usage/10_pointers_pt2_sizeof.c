#include <stdio.h>

void fun_no_size(int arr[]) {
  int i;
  size_t arr_size = sizeof(arr)/sizeof(arr[0]);
  // Should be 8, as pointers are 8 bytes.
  printf("sizeof(arr): %zu\n", sizeof(arr));
  printf("sizeof(arr[0]): %zu\n", sizeof(arr[0]));
  printf("arr_size: %zu\n", arr_size);
  for (i = 0; i < arr_size; i++)
      printf("%d ", arr[i]);
}

void fun(int *arr, size_t arr_size) {
    int i; 
    for (i = 0; i < arr_size; i++) {
        printf("%d ", arr[i]); 
    }
    printf("\n");
}

int main() { 
    int i; 
    int arr[] = {10, 20 ,30, 40};

    // Use of sizeof is fine here
    // IMPORTANT: sizeof() should NEVER be used for 
    //            array parameters inside functions
    //
    //            You can see try this for fun_no_size()
    //            and see what happens...
    size_t n = sizeof(arr)/sizeof(arr[0]); 
    fun(arr, n); 
    fun_no_size(arr); 
    return 0; 
}