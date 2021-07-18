#include "linked_list.h"

void ll_add(struct LinkedList* l_list, int val) {
    struct Node* nptr;
    struct Node *new_node;

    if (!l_list->head) {
        // printf("LinkedList is empty!\n");
        
        l_list->head = (struct Node*) malloc(sizeof(struct Node*));
        l_list->head->val = val;

    } else {
        // printf("LinkedList is NOT empty!\n");
        nptr = l_list->head;

        while ((nptr->next_node)) {
            nptr = nptr->next_node;
        }
        new_node = (struct Node*) malloc(sizeof(struct Node*));
        nptr->next_node = new_node;
        new_node->val = val;
    }
}

int ll_get(struct LinkedList* l_list, size_t index) {
    struct Node* nptr;
    
    nptr = l_list->head;
    if (!nptr) { return -1; }
    if (!index) { return nptr->val; }

    while (nptr && index){
        nptr = nptr->next_node;
        index--;
    }

    // printf("INSIDE: nptr ? nptr->val : -1 ==> %d\n", nptr ? nptr->val : -1);
    return nptr ? nptr->val : -1;
}

void ll_remove(struct LinkedList* l_list, size_t index){
    size_t c_idx;
    struct Node* bptr;
    struct Node* nptr;
    struct Node* tptr;

    c_idx = index;
    
    nptr = l_list->head;
    // printf("index %lu\n", index);
    if (!nptr) { 
        // printf("No head. Exit.\n"); 
        return; 
    }
    if (!index) { 
        bptr = nptr;
        tptr = nptr->next_node;
        l_list->head = tptr;
        // [QUESTION]: Why is this causing me grief????
        // free(bptr);
        return;
    }

    while (nptr && index){
        bptr = nptr;
        nptr = nptr->next_node;
        index--;
    }
    if (nptr) {
        tptr = nptr->next_node;
        bptr->next_node = tptr;
        free(nptr);
    } else {
        return;
        // printf("No node to remove at c_idx=%lu\n", c_idx);
    }
}

void free_node(struct Node* node) {
    if (node->next_node) {
        printf("Going down to the next node. val=%d\n", node->next_node->val);
        free_node(node->next_node);
        // printf("Print order backwards next node. val=%d\n", node->next_node->val);
    }
    printf("Freeing...\n");
    free(node);
}

void ll_destroy(struct LinkedList* l_list) {
    struct Node* node = l_list->head;
    if (node) {
        printf("Starting recursion. val=%d\n", node->val);
        free_node(node);
    }
    // free(l_list->head->next_node->next_node);
    // free(l_list->head->next_node);
    // free(l_list->head);
    printf("Free l_list\n");
    free(l_list);
}

void test_add() {
    struct LinkedList *linked_list;
    linked_list = (struct LinkedList*) malloc(sizeof(struct LinkedList));

    ll_add(linked_list, 5);
    printf("i=%d\n", linked_list->head->val);
    // if((linked_list->head->next_node)) { printf("Is next node of head empty?\n"); }
    ll_add(linked_list, 3);
    printf("i=%d\n", linked_list->head->val);
    printf("j=%d\n", linked_list->head->next_node->val);
    ll_add(linked_list, 1);
    printf("i=%d\n", linked_list->head->val);
    printf("j=%d\n", linked_list->head->next_node->val);
    printf("k=%d\n", linked_list->head->next_node->next_node->val);

    printf("ADDRESS: %0x\n", &linked_list);
}

void test_get() {
    size_t g0; size_t g1; size_t g2;
    struct LinkedList *linked_list;
    linked_list = (struct LinkedList*) malloc(sizeof(struct LinkedList));

    g0 = 0; g1 = 1; g2 = 2;

    printf("g0: l_list[%lu] = %d\n", g0, ll_get(linked_list, g0));
    printf("g1: l_list[%lu] = %d\n", g1, ll_get(linked_list, g1));
    printf("g2: l_list[%lu] = %d\n", g2, ll_get(linked_list, g2));

    printf("\n----\n\n");

    ll_add(linked_list, 5);
    printf("g0: l_list[%lu] = %d\n", g0, ll_get(linked_list, g0));
    printf("g1: l_list[%lu] = %d\n", g1, ll_get(linked_list, g1));
    printf("g2: l_list[%lu] = %d\n", g2, ll_get(linked_list, g2));

    printf("\n----\n\n");

    ll_add(linked_list, 3);
    printf("g0: l_list[%lu] = %d\n", g0, ll_get(linked_list, g0));
    printf("g1: l_list[%lu] = %d\n", g1, ll_get(linked_list, g1));
    printf("g2: l_list[%lu] = %d\n", g2, ll_get(linked_list, g2));

    printf("\n----\n\n");

    ll_add(linked_list, 1); 
    printf("g0: l_list[%lu] = %d\n", g0, ll_get(linked_list, g0));
    printf("g1: l_list[%lu] = %d\n", g1, ll_get(linked_list, g1));
    printf("g2: l_list[%lu] = %d\n", g2, ll_get(linked_list, g2));
    
    printf("ADDRESS: %0x\n", linked_list);
    // QUESTION: Why does free'ing here cause problems?...
    // ll_destroy(linked_list);
}

void test_remove() {
    size_t g0; size_t g1; size_t g2;
    struct LinkedList *linked_list;
    linked_list = (struct LinkedList*) malloc(sizeof(struct LinkedList));

    g0 = 0; g1 = 1; g2 = 2;

    ll_remove(linked_list, g0);
    ll_remove(linked_list, g1);
    ll_remove(linked_list, g2);
   
    printf("\n----\n\n");
    
    ll_add(linked_list, 5);
    printf("g0: l_list[%lu] = %d\n", g0, ll_get(linked_list, g0));
    ll_remove(linked_list, g0);
    ll_remove(linked_list, g1);
    ll_remove(linked_list, g2);

    printf("\n----\n\n");

    ll_add(linked_list, 5);
    ll_add(linked_list, 3);
    printf("g0: l_list[%lu] = %d\n", g0, ll_get(linked_list, g0));
    printf("g1: l_list[%lu] = %d\n", g1, ll_get(linked_list, g1));
    ll_remove(linked_list, g0);
    printf("g0: l_list[%lu] = %d\n", g0, ll_get(linked_list, g0));
    ll_remove(linked_list, g0);
    printf("g0: l_list[%lu] = %d\n", g0, ll_get(linked_list, g0));

    printf("\n----\n\n");

    ll_add(linked_list, 5);
    ll_add(linked_list, 3);
    printf("g0: l_list[%lu] = %d\n", g0, ll_get(linked_list, g0));
    printf("g1: l_list[%lu] = %d\n", g1, ll_get(linked_list, g1));
    printf("\nll_remove(linked_list, g1);\n\n");
    
    ll_remove(linked_list, g1);
    ll_remove(linked_list, g2);
    printf("g0: l_list[%lu] = %d\n", g0, ll_get(linked_list, g0));
    printf("g1: l_list[%lu] = %d\n", g1, ll_get(linked_list, g1));
    
    printf("\nll_remove(linked_list, g1);\n\n");
    ll_remove(linked_list, g0);
    printf("g0: l_list[%lu] = %d\n", g0, ll_get(linked_list, g0));
    printf("g1: l_list[%lu] = %d\n", g1, ll_get(linked_list, g1));

    printf("\n----\n\n");

    ll_add(linked_list, 5);
    ll_add(linked_list, 3);
    ll_add(linked_list, 1); 
    ll_remove(linked_list, g1);
    printf("g0: l_list[%lu] = %d\n", g0, ll_get(linked_list, g0));
    printf("g1: l_list[%lu] = %d\n", g1, ll_get(linked_list, g1));
    printf("g2: l_list[%lu] = %d\n", g2, ll_get(linked_list, g2));
    ll_remove(linked_list, g2);
    printf("g0: l_list[%lu] = %d\n", g0, ll_get(linked_list, g0));
    printf("g1: l_list[%lu] = %d\n", g1, ll_get(linked_list, g1));
    printf("g2: l_list[%lu] = %d\n", g2, ll_get(linked_list, g2));
    ll_remove(linked_list, g0);
    printf("g0: l_list[%lu] = %d\n", g0, ll_get(linked_list, g0));
    printf("g1: l_list[%lu] = %d\n", g1, ll_get(linked_list, g1));
    printf("g2: l_list[%lu] = %d\n", g2, ll_get(linked_list, g2));


    printf("ADDRESS: %0x\n", linked_list);
    ll_destroy(linked_list);
}

int main(int argc, char** argv) {
    test_add();
    test_get();
    test_remove();

    return 0;
}
