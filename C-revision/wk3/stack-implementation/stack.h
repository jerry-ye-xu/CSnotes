#ifndef STACK
#define STACK
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    void* val;
    struct Node* next;
};

struct Stack {
  struct Node *top;
  size_t size;
};

void* pop(struct Stack* s);
void push(struct Stack* s, void* data, size_t nbytes);
void* peek(struct Stack* s);
void free_stack(struct Stack* s);

#endif
