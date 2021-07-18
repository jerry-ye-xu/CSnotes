#include <stdio.h>

#define CONSTANT_JERRY 30

int main() {
    printf("CONSTANT_JERRY=%d\n", CONSTANT_JERRY);
    printf("CONSTANT_JERRY=%d", CONSTANT_JERRY);

    return 0;
}