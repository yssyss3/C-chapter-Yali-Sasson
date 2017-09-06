#include <malloc.h>
#include <stdio.h>
#include "queue.h"

Queue* newQueue(int value){
    Queue* new = (Queue*)malloc(sizeof(Queue));
    if(new == NULL){
        printf("error creating queue!\n");
        return NULL;
    }
    new->length = 1;
    new->list = newList(value);
}

void push(Queue* q, int value){
    if(q->list != NULL){
        append(q->list, value);
    }
    else{
        q->list = newList(value);
    }
    q->length++;
}

int pop(Queue* q){
    int value;
    if(q->list == NULL){
        printf("error popping from empty queue\n");
        exit(1);
    }
    value = q->list->value;

    /*setting the second node to ve the first one if exists
     * if not deleting the list and setting it to NULL */
    if(q->list->next != NULL){
        Node* newFirst = q->list->next;
        removeFromList(q->list);
        q->list = newFirst;
    }
    else{
        deleteList(q->list);
        q->list = NULL;
    }
    q->length--;
    return value;
}

int peek(Queue* q){
    if(q->list == NULL){
        printf("error peeking into an empty queue!\n");
        exit(1);
    }
    return  q->list->value;
}

void deleteQueue(Queue* q){
    deleteList(q->list);
    free(q);
}