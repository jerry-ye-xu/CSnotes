
#ifndef LINKEDLIST
#define LINKEDLIST
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int val;
    struct Node* next_node;
};

struct LinkedList {
    struct Node* head;
    size_t size;
};

void ll_add(struct LinkedList* l_list, int val);
void ll_remove(struct LinkedList* l_list, size_t index);
void ll_destroy(struct LinkedList* l_list);
int ll_get(struct LinkedList* l_list, size_t index);

#endif
