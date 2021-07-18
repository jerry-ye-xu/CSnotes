#include<stdio.h>

int main()
{
    int a = 12;
    void *ptr = (int *)&a;
    // void pointers CANNOT be dereferenced.
    printf("%d", *ptr);
    printf("%d", *(int *)ptr);
    getchar();
    return 0;
}