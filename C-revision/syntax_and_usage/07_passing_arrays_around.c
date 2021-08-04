#include <stdio.h>

void printArr(int *arr, int size) {
    int i;
    for (i = 0; i < size; ++i) {
      printf("arr[%d]=%d\n", i, arr[i]);
   }
}
void printArrString(char *arr, int size) {
    int i;
    for (i = 0; i < size; ++i) {
      printf("arr[%d]=%c\n", i, arr[i]);
   }
}

void passAsPointer(int *arr, int size) {
    printf("\npassAsPointer\n");
    printArr(arr, size);
}

void passAsSize(int arr[4], int size) {
    printf("\npassAsSize\n");
    printArr(arr, size);
}

void passAsSquareBracket(int arr[], int size) {
    printf("\npassAsSquareBracket\n");
    printArr(arr, size);
}

int main(int argc, char** argv) {
    int size = 4;
    int arr[] = {1, 2, 3, 4};

    char text[] = "Word";

    passAsPointer(arr, size);
    passAsSize(arr, size);
    passAsSquareBracket(arr, size);

    printf("\nprintArrString\n");
    printArrString(text, size);
}
