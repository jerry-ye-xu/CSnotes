#include "point.h"

struct Node* create_node(int x, int y) {
    struct Node* node = (struct Node*) malloc(sizeof(struct Node*));

    node->x = x; node->y = y;

    return node;
}

bool assert_coordinates(struct Node *node, int x, int y) {
    return node->x == x && node->y == y ? 1 : 0;
}

bool compare_nodes(struct Node *node, struct Node *other) {
    return node->x == other->x && node->y == other->y ? 1 : 0;
}