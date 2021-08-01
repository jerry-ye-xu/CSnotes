#include "stack.h"

void push(struct Stack* s, void* data, size_t nbytes) {
    struct Node *node = (struct Node*) malloc(sizeof(struct Node));
    if (node == NULL) { exit(EXIT_FAILURE); }
    memset(node, 0, sizeof(struct Node));

    // printf("sizeof(struct Node): %lu\n", sizeof(struct Node));

    // node->val = malloc(nbytes);
    // if (node->val == NULL) { exit(EXIT_FAILURE); }
    node->val = data;

    if(!s->top) {
        s->top = node;
    } else {
        struct Node *prev_top = s->top;
        node->next = prev_top;
        s->top = node;
    }
    s->size++;
}

void* pop(struct Stack* s) {
    if(!s->top) {
        struct Node *node = (struct Node*) malloc(sizeof(struct Node));
        if (node == NULL) { exit(EXIT_FAILURE); }
        node->val = (void*) -1;
        return node;
    } else {
        struct Node *node_to_pop = s->top;
        s->top = s->top->next;
        s->size--;
        return node_to_pop;
    }
}

void* peek(struct Stack* s) {
    if(!s->top) {
        return pop(s);
    } else {
        return s->top;
    }
}

void free_stack(struct Stack* s) {
    size_t stack_size = s->size;
    if (stack_size) {
        while(stack_size) {
            void* data = pop(s);
            free(data);
            stack_size--;
        }
    }
    free(s);
}