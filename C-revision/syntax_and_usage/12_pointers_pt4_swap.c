#include <stdio.h>

void swap(int *px, int *py) { 
    *px = *px - *py; 
    printf("*px=%d\n", *px);
    printf("*py=%d\n", *py);
    *py = *px + *py; 
    printf("*px=%d\n", *px);
    printf("*py=%d\n", *py);
    *px = *py - *px; 
    printf("*px=%d\n", *px);
    printf("*py=%d\n", *py);
}

void run_swap_int() {
    int x = 5;
    int y = 1;
    int* px = &x;
    int* py = &y;
    
    swap(px, py);
    
    printf("x=%d\n", x);
    printf("y=%d\n", y);
}

/* Swaps strings by swapping pointers */ 
void swap1(char **str1_ptr, char **str2_ptr) {
  char *temp = *str1_ptr;
  *str1_ptr = *str2_ptr;
  *str2_ptr = temp;
}  

void run_swap_string() {
    char *str1 = "geeks";
    char *str2 = "forgeeks";
    swap1(&str1, &str2);
    printf("run_swap_string():\n");
    printf("str1 is %s, str2 is %s\n", str1, str2);
}
void swap2(char *str1_ptr[], char *str2_ptr[]) {
  char *temp = *str1_ptr;
  *str1_ptr = *str2_ptr;
  *str2_ptr = temp;
}  

void run_swap_string_with_arr() {
    printf("run_swap_string_with_arr():\n");
    char str1[10] = "geeks";
    char str2[10] = "forgeeks";
    char* pt1 = &str1;
    char* pt2 = &str2;
    swap2(&str1, &str2);
    // swap1(pt1, pt2);
    printf("str1 is %s, str2 is %s\n", str1, str2);
}

int main() {
    // run_swap_int();
    // run_swap_string();
    run_swap_string_with_arr();

    return 0;
}