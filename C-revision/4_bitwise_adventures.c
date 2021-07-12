#include <stdio.h>
#include <stdlib.h>

/*
    4_bitwise_adventures.c:7:13: note: previous implicit declaration is here

    ^ what this is saying is that bin_repr is found afterwards, so at the main()
    code it assumes a return type.

    To remove this error, I changed the order of function declarations around.
*/

/*
    4_bitwise_adventures.c:23:12: warning: address of stack memory associated
    with local variable 'bin_arr' returned

    > char bin_arr[nbits];

    ^ Declaring char* arr[n] will allocate space on the stack.
    This means that it will automatically be released when the current block
    goes out of scope.

    Hence, we want to either:

    1) Use "static"
    2) Allocate the space to the heap using "malloc".
*/

/*
    https://vorpus.org/blog/why-does-calloc-exist/
    https://www.geeksforgeeks.org/dynamic-memory-allocation-in-c-using-malloc-calloc-free-and-realloc/


*/

void basic_bit_shifting() {
    /*
        10000 >> 1 = 1000
        01110 >> 1 = 0011
        00110 >> 1 = 0001
    */
    int a = 16;
    int b = 14;
    int c = 3;
    printf("a >> 1=%d\n", a >> 1);
    printf("a >> 2=%d\n", a >> 2);
    printf("a >> 3=%d\n", a >> 3);
    printf("b >> 1=%d\n", b >> 1);
    printf("b >> 2=%d\n", b >> 2);
    printf("b >> 3=%d\n", b >> 3);
    printf("c >> 1=%d\n", c >> 1);
    printf("c >> 2=%d\n", c >> 2);
    printf("c >> 3=%d\n", c >> 3);
}

char* bin_repr(unsigned n, int nbits) {
    // printf("nbits=%d\n", nbits);
    unsigned i;
    // Printing the unsigned i unsigned int returns the maximum
    // printf("i=%d\n", i);

    unsigned idx = 0;
    char* binary_repr = (char*) malloc(nbits);

    // Start with 1....0 (31 zeros) and shift along
    for (i = 1 << (nbits - 1); i > 0; i = i / 2) {
        // (n & i) ? printf("1") : printf("0");
        // printf("i=%d\n", i);
        int val = (n & i) ? '1' : '0';
        binary_repr[idx] = val;
        idx++;
    }
    return binary_repr;
}

unsigned int start_idx(char* binary_repr, int nbits) {
    unsigned i;
    for (i = 0; i < nbits; i++) {
        // printf("binary_repr[i]: %c\n", binary_repr[i]);
        if (binary_repr[i] == '1') {
            return i;
        }
    }
    return nbits - 1;
}

void printb(int x) {
    int nbits = sizeof(x) * 8;
    char *x_bin = bin_repr(x, nbits);
    /*
        The following 2 statements are equivalent.
        char *x_bin = arr;
        char *x_bin = &arr[0];
    */
    unsigned idx = start_idx(x_bin, nbits);
    // Print the entire array starting from idx
    printf("%s\n", &x_bin[idx]);

    free(x_bin);
}

int main(int argc, char **argv) {

    /* 111100 */
    int w = 503;
    int x = 127;
    int y = 60;
    int z = 14;
    printb(w);
    printb(x);
    printb(y);
    printb(z);

    int a = 0;
    int b = 1;
    int c = 3;
    printb(a);
    printb(b);
    printb(c);

    int w1 = 503;
    int w2 = w1 >> 1;
    int w3 = w2 >> 1;
    int w4 = w3 >> 1;
    int w5 = w4 >> 1;
    printb(w1);
    printb(w2);
    printb(w3);
    printb(w4);
    printb(w5);

    // Best not to use this if you don't have a else if...
    // 1 ? printf("true") : void f();

    return 0;
}
