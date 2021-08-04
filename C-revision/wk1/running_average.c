#include <stdio.h>
#include <math.h>

double calc_mean(double x_bar, double x, int len) {
    return (x_bar * (len-1) + x) / (len);
}

double calc_var(double x_var, double x_bar, double x_bar_prev, int x, int len
) {
    return (x_var + (x - x_bar_prev) * (x - x_bar))/len;
}

int main(int argc, char** argv) {
    int next_int;
    int curr_len = 0;
    double prev_mean = 0;
    double curr_mean = 0;
    double curr_var = 0;
    double curr_std = 0;
    
    while (1) {
        printf("Enter an integer: ");
        if(scanf("%d", &next_int)) {
            printf("int=%d\n", next_int);
            prev_mean = curr_mean;
            curr_mean = calc_mean(curr_mean, next_int, ++curr_len);
            curr_var = calc_var(curr_var, curr_mean, prev_mean, next_int, curr_len);
            curr_std = sqrt(curr_var);

            printf("mean: %4f\n", curr_mean);
            printf("var: %4f\n", curr_var);
            printf("std: %4f\n", curr_std);
        } else {
            printf("Input was not an integer.");
            return -1;
        }
    }
}
