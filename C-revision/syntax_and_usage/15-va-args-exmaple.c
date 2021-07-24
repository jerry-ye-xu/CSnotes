#include <stdarg.h>
#include <stdio.h>

int sum(int num_args, ...) {
    int i;
    int total = 0;
    va_list curr;

    va_start(curr, num_args);
    for (i = 0; i < num_args; i++) {
        total += va_arg(curr, int);
    }
    va_end(curr);

    return total;
}

int main() {
    printf("Sum of a whole bunch of numbers: %d\n", sum(5, 1, 2, 3, 4, 5));
}
