#include <stdio.h>

/*
    int **data;

    ^ Can be intepreted in the following ways:

    1) Pointer to pointer of int value
    2) Pointer to an array of int values
    3) Array of pointers that each point to an int value
    4) Array of pointers that each point to an array of int values

    If you think about '*' as an "array" in data:

    1) size == 1 || size == 1
    2) size == 1 || size >= 1
    3) size >= 1 || size == 1
    4) size >= 1 || size >= 1
*/

/*
    Pointers have "&" and "*" that essentially undo each other.
*/

void try_this() {
    int array[] = {1, 2, 3};

    printf("%d\n", array[-1]);
}

int main() {
    int size = 4;
    int arr[] = {1, 2, 3, 4};

    int age = 21;
    char name[] = "Jerry";
    int *pt = &age;

    char text[] = "Word";

    int i = 0;
    int j = 1;
    printf("arr[%d]=%d\n", i, arr[i]);
    printf("arr[%d]=%c\n", i, text[i]);
    printf("arr[%d]=%d\n", j, arr[j]);
    printf("arr[%d]=%c\n", j, text[j]);

    printf("VAL: age     %d\n", age);
    printf("VAL: *pt=    %d\n", *pt);
    printf("VAL: *&age=  %d\n", *&age);
    printf("VAL: *&*&age=%d\n", *&*&age);
    printf("VAL: *&*pt=  %d\n", *&*pt);
    printf("VAL: *&*&*pt=%d\n", *&*&*pt);

    printf("ADDR: &age=  %0x\n", &age);
    printf("ADDR: &*&age=%0x\n", &*&age);
    printf("ADDR: pt=    %0x\n", pt);
    printf("ADDR: &*pt=  %0x\n", &*pt);

    try_this();

    return 0;
}
