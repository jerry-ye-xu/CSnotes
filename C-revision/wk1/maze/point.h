#ifndef POINT
#define POINT
#include <stdlib.h>
#include <stdbool.h>

struct Node {
    int x;
    int y;
};

struct Node* create_node(int x, int y);
bool assert_coordinates(struct Node *node, int x, int y);
bool compare_nodes(struct Node *node, struct Node *other);

#endif
