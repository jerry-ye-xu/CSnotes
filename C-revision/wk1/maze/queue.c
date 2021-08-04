#include "queue.h"

struct Queue* create_queue() {
    struct Queue *q;
    q = (struct Queue*) malloc(sizeof(struct Queue));
    q->front = 0;
    q->rear = -1;
    return q;
}

int is_empty(struct Queue* q) {
    return q->rear < 0 ? 1 : 0;
}

void print_queue(struct Queue* q) {
    int i;
    if (is_empty(q)) { printf("Queue is empty.\n"); }
    else {
        printf("Queue: [ ");
        for (i = q->front; i < (q->rear) + 1; i++) {
            printf("(%d %d) ", q->items[i]->x, q->items[i]->y);
        }
        printf("]\n");
    }
}

void enqueue(struct Queue* q, struct Node *node) {
    if (q->rear == SIZE - 1) { printf("Queue is full.\n"); return; }
    else {
        q->rear++;
        // printf("node = (%d %d)\n", node->x, node->y);
        // printf("rear=%d\n", q->rear)
        q->items[q->rear] = node;
    }
}

struct Node* dequeue(struct Queue* q) {
    struct Node* node;

    if (is_empty(q)) {
        node = (struct Node*) malloc(sizeof(struct Node));
        node->x = -1; node->y = -1;
    } else {
        node = q->items[q->rear];
        // printf("node = (%d %d)\n", node->x, node->y);
        // printf("rear=%d\n", q->rear);
        q->items[q->rear] = NULL;
        q->rear--;
    }

    return node;
}
