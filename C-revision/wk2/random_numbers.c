
#include <stdio.h>
#include <stdlib.h>

void file_input(char* file) {
    int num;
    int i = 0;

    FILE* f = fopen(file, "w");
    if (f == NULL) { printf("Error opening file.\n"); exit(1); }
    while (i < 50) {
        num = rand();
        fprintf(f, "%d\n", num);
        i++;
    }
    fclose(f);
}
void file_output(char* file) {
    FILE* f = fopen(file, "r");
    if (f == NULL) { printf("Error opening file.\n"); exit(1); }
    
    char buf[512];
    while(fgets(buf, 512, f)) {
        printf("%s", buf);
    }
    fclose(f);
}

int main() {
    char *file_path = "numbers.txt";
    file_input(file_path);
    file_output(file_path);
}
