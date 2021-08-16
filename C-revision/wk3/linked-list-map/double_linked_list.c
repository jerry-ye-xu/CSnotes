#include <stdlib.h>

#include "double_linked_list.h"

void dll_print_int(struct DoubleLinkedList* dll){
    struct Node* curr_node = dll->head;
    for (int i = 0; i < dll->size; i++){
        printf(
            "dll[%d] = (%d, %d)\n", i,
            *(int*) curr_node->key,
            *(int*) curr_node->value
        );
        curr_node = curr_node->next;
    }
}

void dll_add(struct DoubleLinkedList* dll, void* key, void* value) {
    struct Node* node = malloc(sizeof(struct Node));

    // Empty dll.
    if (dll->head == NULL) {
        node->key = key;
        node->value = value;
        dll->head = node;
        dll->tail = node;
    // Add to tail
    } else {
        node->key = key;
        node->value = value;
        struct Node* curr_tail = dll->tail;
        dll->tail = node;
        node->prev = curr_tail;
    }
    dll->size++;
}

void* dll_get(struct DoubleLinkedList* dll, void* key, int (*eq)(void*, void*)) {
    struct Node* curr_node = dll->head;
    for (int i = 0; i < dll->size; i++) {
        // printf("eq(curr_node->key, key): %d\n", eq(curr_node->key, key));
        if (eq(curr_node->key, key)) {
            return curr_node;
        }
        curr_node = curr_node->next;

    return NULL;
}

void* dll_rm(struct DoubleLinkedList* dll, void* key, int (*eq)(void*, void*)) {
    struct Node* curr_node = dll->head;
    for (int i = 0; i < dll->size; i++) {
        // printf("eq(curr_node->key, key): %d\n", eq(curr_node->key, key));
        if (eq(curr_node->key, key)) {
            left = curr_node->prev;
            right = curr_node->next;
            left->next = right;
            right->prev = left;
            curr_node->prev = NULL;
            curr_node->next = NULL;
            dll->size--;
            return curr_node;
        }
        curr_node = curr_node->next;
    }
    return NULL;
}