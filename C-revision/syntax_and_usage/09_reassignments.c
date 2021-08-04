#include <stdio.h>

int main(int argc, char** argv) {
    int x;
    double y;

    x = 5;
    printf("x = %d\n", x);
    x = 4;
    printf("x = %d\n", x);

    y = 6 / 4;
    printf("6/4 = %f\n", y);
    printf("6/4 = %d\n", (int) y);

    printf("(int) 1.812 = %d\n", (int) 1.812);

    return 0;
}
