#include "double_linked_list.h"

int min_(int x, int y) {
    return x < y ? x : y;
}

int max_(int x, int y) {
    return x > y ? x : y;
}

/*
    Pass this in as a function ptr so the linkedlist
    can handle keys of different value types.
*/
int eq_int(void* x, void* y) {
    return *(int*) x == *(int*) y ? 1 : 0;
}

int test_empty_list() {
    int res;

    struct DoubleLinkedList* dll = malloc(sizeof(struct DoubleLinkedList));
    dll->size = 0;

    res = !dll->size ? 1 : 0;
    res = min_(dll->head == NULL ? 1 : 0, res);

    int (*eq)(void*, void*) = eq_int;
    res = min_(dll_get(dll, 0, eq) == NULL ? 1 : 0, res);
    // printf("dll_get(dll, 0, eq): %p\n", dll_get(dll, 0, eq));

    return res;
}

int test_add_one() {
    int res;
    int x = 1; int y = 11;
    int* k = &x; int* v = &y;

    struct DoubleLinkedList* dll = malloc(sizeof(struct DoubleLinkedList));
    dll->size = 0;
    dll_add(dll, k, v);

    res = dll->size ? 1 : 0;
    res = *(int*) dll->head->key == 1 ? 1 : 0;
    res = min_(*(int*) dll->head->value == 11 ? 1 : 0, res);

    return res;
}

int main(int argc, char** argv) {
    int res = test_empty_list();
    printf("|%d| test_empty_list\n", res);

    res = min_(test_add_one(), res);
    printf("|%d| test_add_one\n", res);

    return res ? 0 : 1;
}