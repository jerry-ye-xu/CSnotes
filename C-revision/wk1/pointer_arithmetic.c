#include <stdio.h>

int main() {
    int arr[] = {1, 2, 3, 4, 5};

    int *p = arr;

    printf("(p+2) = %p\n", (p+2));
    printf("(p+3) = %p\n", (p+3));
    printf("(p+3)[0] = %d\n", (p+3)[0]);
    printf("&(p+3)[0] = %p\n", &(p+3)[0]);
    printf("p = %p\n", p);
    printf("&*p = %p\n", &*p);
    printf("&(p[0]) = %p\n", &(p[0]));
    // printf("&((p[1])[1]) = %p\n", &((p[1])[1]));
    printf("&p = %p\n", &p);
    // printf("&(p+0) = %p\n", &(p+0));
}
