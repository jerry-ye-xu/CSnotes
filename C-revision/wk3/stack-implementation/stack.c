#include "stack.h"

void push(struct Stack* s, void* data, size_t nbytes) {
    struct Node *node = (struct Node*) malloc(sizeof(struct Node*)); 
    if (node == NULL) { exit(EXIT_FAILURE); }
    
    if(!s->top) {
        node->val = malloc(nbytes);
        if (node->val == NULL) { exit(EXIT_FAILURE); }
        node->val = data;
        s->top = node;
    } else {
        struct Node *prev_top = s->top;
        node->val = malloc(nbytes);
        if (node->val == NULL) { exit(EXIT_FAILURE); }
        node->val = data;
        node->next = prev_top;
        s->top = node;
    }
    s->size++;
}

void* pop(struct Stack* s) {
    if(!s->top) {
        struct Node *node = (struct Node*) malloc(sizeof(struct Node*));
        if (node == NULL) { exit(EXIT_FAILURE); }
        node->val = (void*) -1;
        return node;
    } else {
        struct Node *node_to_pop = s->top;
        s->top = s->top->next;
        return node_to_pop;
    } 
}

void* peek(struct Stack* s) {
    if(!s->top) {
        struct Node *node = (struct Node*) malloc(sizeof(struct Node*));
        if (node == NULL) { exit(EXIT_FAILURE); }
        node->val = (void*) -1;
        return node;
    } else {
        return s->top;
    }
}
