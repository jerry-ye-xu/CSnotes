#include <stdio.h>
#include <stdlib.h>
#include<string.h>

#include "stack.h"

int min_(int x, int y) {
    return x < y ? x : y;
}

int max_(int x, int y) {
    return x > y ? x : y;
}

int test_empty_stack_peek() {
    struct Stack* stack = malloc(sizeof(struct Stack));
    memset(stack, 0, sizeof(struct Stack));
    stack->size = 0;

    void *top = peek(stack);
    int result = *(int*)top;

    free(top);
    free(stack);

    return result == -1 ? 1 : 0;
}

int test_push_into_empty_stack() {
    int data = 50;
    int *d_ptr = &data;
    struct Stack* stack = malloc(sizeof(struct Stack));
    memset(stack, 0, sizeof(struct Stack));
    stack->size = 0;

    push(stack, d_ptr, sizeof(d_ptr));
    void *top = peek(stack);

    size_t size = stack->size;
    int result = *(int *)((struct Node*)top)->val;

    free_stack(stack);

    return result == 50 && size ? 1 : 0;
}

int test_push_into_non_empty_stack() {
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));
    memset(stack, 0, sizeof(struct Stack));

    // Add first element
    stack->size = 0;
    int data = 1;
    int *d_ptr = &data;
    push(stack, d_ptr, sizeof(d_ptr));


    // Add second element and test
    char text[6] = "hello";
    char *t_ptr = text;
    push(stack, t_ptr, sizeof(t_ptr));
    void *top = peek(stack);

    size_t size = stack->size;
    char* text_data = (char *)((struct Node*)top)->val;
    printf("text_data: %s\n", text_data);

    int expected = strcmp(text_data, text);
    printf("%d\n", expected);

    free_stack(stack);

    return !expected && size == 2 ? 1 : 0;
}

int test_push_into_non_empty_stack_then_pop() {
    struct Node* node_pop;
    struct Stack* stack = (struct Stack*) malloc(sizeof(struct Stack));
    memset(stack, 0, sizeof(struct Stack));

    // Add first element
    stack->size = 0;
    int data = 1;
    int *d_ptr = &data;
    push(stack, d_ptr, sizeof(d_ptr));

    // Add second element
    char text[6] = "hello";
    char *t_ptr = text;
    push(stack, t_ptr, sizeof(t_ptr));

    // Pop and test
    node_pop = (struct Node *) pop(stack);
    char* text_pop = (char *) node_pop->val;
    int expected = strcmp(text_pop, text);
    int size = (int) stack->size == 1;

    free(node_pop);
    free_stack(stack);

    return !expected && size == 1 ? 1 : 0;

}

int main(int argc, char** argv) {
    int res;
    int pass = 1;
    res = test_empty_stack_peek();
    printf("| %d | test_empty_stack_peek\n", pass);
    pass = min_(res, pass);

    res = test_push_into_empty_stack();
    printf("| %d | test_push_into_empty_stack\n", pass);
    pass = min_(res, pass);

    res = test_push_into_non_empty_stack();
    printf("| %d | test_push_into_non_empty_stack\n", pass);
    pass = min_(res, pass);

    res = test_push_into_non_empty_stack_then_pop();
    printf("| %d | test_push_into_non_empty_stack_then_pop\n", pass);
    pass = min_(res, pass);

    return pass ? 0 : 1;
}
