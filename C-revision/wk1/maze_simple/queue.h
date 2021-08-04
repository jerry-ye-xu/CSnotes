#ifndef QUEUE
#define QUEUE
#include <stdio.h>
#include <stdlib.h>

#include "point.h"

#define SIZE 50

struct Queue {
  struct Node *items[SIZE];
  int front;
  int rear;
};

struct Queue* create_queue();
void enqueue(struct Queue* q, struct Node *node);
struct Node* dequeue(struct Queue* q);
int is_empty(struct Queue* q);
void print_queue(struct Queue* q);

#endif
