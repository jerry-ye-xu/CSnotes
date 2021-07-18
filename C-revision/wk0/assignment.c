#include <stdio.h>

int main() {
    int x, y;

    x = 5;
    y = x;

    x = 10;
    printf("y=%d\n", y);
    printf("x=%d\n", x);
}