#include <string.h>
#include "queue.h"

int min_(int x, int y) {
    return x < y ? x : y;
}

int max_(int x, int y) {
    return x > y ? x : y;
}

bool test_empty_queue() {
    struct Queue *queue;
    struct Node *ret_node;
    bool test_res = 1;

    queue = create_queue();
    test_res = min_(test_res, is_empty(queue));
    
    ret_node = dequeue(queue);
    test_res = min_(test_res, assert_coordinates(ret_node, -1, -1));    

    return test_res;
}

bool test_add_one_node() {
    struct Queue *queue;
    struct Node *ret_node;
    bool test_res = 1;

    queue = create_queue();
    enqueue(queue, create_node(1, 1));
    test_res = min_(test_res, is_empty(queue) == 0);
    ret_node = dequeue(queue);
    test_res = min_(test_res, assert_coordinates(ret_node, 1, 1));
    test_res = min_(test_res, is_empty(queue));

    enqueue(queue, create_node(3, 4));
    test_res = min_(test_res, is_empty(queue) == 0);
    ret_node = dequeue(queue);
    test_res = min_(test_res, is_empty(queue));
    test_res = min_(test_res, assert_coordinates(ret_node, 3, 4));

    return test_res;
}

bool test_add_multiple_nodes() {
    struct Queue *queue;
    struct Node *ret_node;
    struct Node *node0 = create_node(2, 2);
    struct Node *node1 = create_node(3, 4);
    struct Node *node2 = create_node(2, 1);
    struct Node *node3 = create_node(5, 4);
    bool test_res = 1;

    queue = create_queue();
    enqueue(queue, node0);
    enqueue(queue, node1);
    enqueue(queue, node2);
    enqueue(queue, node3);
    test_res = min_(test_res, is_empty(queue) == 0);
    ret_node = dequeue(queue);
    test_res = min_(test_res, assert_coordinates(ret_node, 5, 4));
    ret_node = dequeue(queue);
    test_res = min_(test_res, assert_coordinates(ret_node, 2, 1));
    ret_node = dequeue(queue);
    test_res = min_(test_res, assert_coordinates(ret_node, 3, 4));
    ret_node = dequeue(queue);
    test_res = min_(test_res, assert_coordinates(ret_node, 2, 2));
    test_res = min_(test_res, is_empty(queue));
    ret_node = dequeue(queue);
    test_res = min_(test_res, assert_coordinates(ret_node, -1, -1));

    return test_res; 
}

bool test_add_multiple_nodes_add_and_remove() {
    struct Queue *queue;
    struct Node *ret_node;
    struct Node *node0 = create_node(2, 2);
    struct Node *node1 = create_node(3, 4);
    struct Node *node2 = create_node(2, 1);
    struct Node *node3 = create_node(5, 4);
    bool test_res = 1;

    // QUESTION: Why can't you do this?
    /*
        enqueue(queue, create_node(2, 2)); 
        printf("queue->items[0]->x: (%d, %d)\n", queue->items[0]->x, queue->items[0]->y);
        enqueue(queue, create_node(3, 4)); 
        printf("queue->items[0]->x: (%d, %d)\n", queue->items[0]->x, queue->items[0]->y);
        enqueue(queue, create_node(2, 1)); 
        printf("queue->items[0]->x: (%d, %d)\n", queue->items[0]->x, queue->items[0]->y);
        enqueue(queue, create_node(5, 4)); 
        printf("queue->items[0]->x: (%d, %d)\n", queue->items[0]->x, queue->items[0]->y);
        
        ret_node = dequeue(queue);
        ret_node = dequeue(queue);
        ret_node = dequeue(queue);
        ret_node = dequeue(queue);
        test_res = min_(test_res, assert_coordinates(ret_node, 2, 2));
        printf("test_res: %d\n", test_res);
        printf("ret_node = (%d %d)\n", ret_node->x, ret_node->y);
    */

    queue = create_queue();
    enqueue(queue, node0);
    ret_node = dequeue(queue);
    test_res = min_(test_res, assert_coordinates(ret_node, 2, 2));
    enqueue(queue, node0);
    enqueue(queue, node1);
    enqueue(queue, node2);
    enqueue(queue, node3);
    test_res = min_(test_res, is_empty(queue) == 0);
    ret_node = dequeue(queue);
    test_res = min_(test_res, assert_coordinates(ret_node, 5, 4));
    ret_node = dequeue(queue);
    test_res = min_(test_res, assert_coordinates(ret_node, 2, 1));
    ret_node = dequeue(queue);
    test_res = min_(test_res, assert_coordinates(ret_node, 3, 4));
    ret_node = dequeue(queue);
    test_res = min_(test_res, assert_coordinates(ret_node, 2, 2));
    test_res = min_(test_res, is_empty(queue));
    ret_node = dequeue(queue);
    test_res = min_(test_res, assert_coordinates(ret_node, -1, -1));
    test_res = min_(test_res, is_empty(queue));

    return test_res; 
}

bool test_add_multiple_nodes_multiple_add_and_remove() {
    struct Queue *queue;
    struct Node *ret_node;
    struct Node *node0 = create_node(2, 2);
    struct Node *node1 = create_node(3, 4);
    struct Node *node2 = create_node(2, 1);
    struct Node *node3 = create_node(5, 4);
    struct Node *node4 = create_node(1, 5);
    struct Node *node5 = create_node(4, 3);
    struct Node *node6 = create_node(2, 4);
    bool test_res = 1;

    queue = create_queue();
    enqueue(queue, node0);
    ret_node = dequeue(queue);
    test_res = min_(test_res, assert_coordinates(ret_node, 2, 2));
    enqueue(queue, node0);
    enqueue(queue, node1);
    enqueue(queue, node2);
    enqueue(queue, node3);
    // [ (2, 2) (3, 4) (2, 1) (5, 4) ]
    test_res = min_(test_res, is_empty(queue) == 0);
    ret_node = dequeue(queue);
    test_res = min_(test_res, assert_coordinates(ret_node, 5, 4));
    ret_node = dequeue(queue);
    test_res = min_(test_res, assert_coordinates(ret_node, 2, 1));
    test_res = min_(test_res, is_empty(queue) == 0);
    // [ (2, 2) (3, 4) ]

    enqueue(queue, node4);
    enqueue(queue, node5);
    // [ (2, 2) (3, 4) (1, 5) (4, 3) ]
    ret_node = dequeue(queue);
    test_res = min_(test_res, assert_coordinates(ret_node, 4, 3));
    ret_node = dequeue(queue);
    test_res = min_(test_res, assert_coordinates(ret_node, 1, 5));
    ret_node = dequeue(queue);
    test_res = min_(test_res, assert_coordinates(ret_node, 3, 4));
    test_res = min_(test_res, is_empty(queue) == 0);
    // [ (2, 2) ]

    ret_node = dequeue(queue);
    test_res = min_(test_res, assert_coordinates(ret_node, 2, 2));
    test_res = min_(test_res, is_empty(queue));
    ret_node = dequeue(queue);
    test_res = min_(test_res, assert_coordinates(ret_node, -1, -1));
    ret_node = dequeue(queue);
    test_res = min_(test_res, assert_coordinates(ret_node, -1, -1));
    ret_node = dequeue(queue);
    test_res = min_(test_res, assert_coordinates(ret_node, -1, -1));

    enqueue(queue, node6);
    ret_node = dequeue(queue);
    test_res = min_(test_res, assert_coordinates(ret_node, 2, 4));

    return test_res; 
}

int main(int argc, char** argv) {
    bool t = true;
    bool tt;
    tt = test_empty_queue();
    printf("|%d| test_empty_queue()\n", tt);
    t = min_(t, tt);
    
    tt = test_add_one_node();
    printf("|%d| test_add_one_node()\n", tt);
    t = min_(t, tt);

    tt = test_add_multiple_nodes();
    printf("|%d| test_add_multiple_nodes()\n", tt);
    t = min_(t, tt);

    tt = test_add_multiple_nodes_add_and_remove();
    printf("|%d| test_add_multiple_nodes_add_and_remove()\n", tt);
    t = min_(t, tt);

    tt = test_add_multiple_nodes_multiple_add_and_remove();
    printf("|%d| test_add_multiple_nodes_multiple_add_and_remove()\n", tt);
    t = min_(t, tt);

    return t ? 0: -1;
}
