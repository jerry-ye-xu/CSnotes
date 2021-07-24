#ifndef STACK
#define STACK
#include <stdio.h>
#include <stdlib.h>

struct Node {
    void* val;
    struct node* next;
};

struct Stack {
  struct Node *top;
  size_t size;
};

void* pop(struct Stack* s);
void push(struct Stack* s, void* data, size_t nbytes);
void* peek(struct Stack* s);

#endif
