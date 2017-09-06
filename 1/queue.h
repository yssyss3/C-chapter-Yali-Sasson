#ifndef LIST_QUEUE_H
#define LIST_QUEUE_H

#include "list.h"

struct Queue{
    int length;
    Node* list;
};
typedef struct Queue Queue;

Queue* newQueue(int value);
void push(Queue* q, int value);
int pop(Queue* q);
int peek(Queue* q);
void deleteQueue(Queue* q);


#endif //LIST_QUEUE_H
