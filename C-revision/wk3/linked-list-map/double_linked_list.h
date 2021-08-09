#ifndef DOUBLELINKEDLIST
#define DOUBLELINKEDLIST

#include <stdio.h>
#include <stdlib.h>

struct DoubleLinkedList {
    struct Node* head;
    struct Node* tail;
    size_t size;
};

struct Node {
    void* key;
    void* value;
    struct Node* prev;
    struct Node* next;
};

void dll_add(struct DoubleLinkedList* dll, void* key, void* value);
void* dll_rm(struct DoubleLinkedList* dll, void* key, int (*eq)(void*, void*));
void* dll_get(struct DoubleLinkedList* dll, void* key, int (*eq)(void*, void*));
void dll_destroy(struct DoubleLinkedList* dll);
void dll_print_int(struct DoubleLinkedList* dll);

#endif
