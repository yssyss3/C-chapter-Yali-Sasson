#include "list.h"

#include <stdio.h>
#include <stdlib.h>




Node* newList(int value){
    Node* first;
    ListInfo* info;

    first = (Node*)(malloc(sizeof(Node)));
    if(first == NULL){
        printf("error creating list\n");
        return NULL;
    }

    first->value = value;
    first->next = NULL;
    first->prev = NULL;

    info = (ListInfo*)malloc(sizeof(ListInfo));
    if(info == NULL){
        printf("error creating list\n");
        return NULL;
    }

    info->avg = (float)value;
    info->length = 1;
    info->first = first;
    info->last = first;

    first->info = info;
    return first;
}


void deleteList(Node* list){
    Node* temp = list->info->first;
    list = temp;
    free(list->info);

    while(temp!=NULL){
        temp = list->next;
        free(list);
        list = temp;
    }
}


void append(Node* list, int newValue){
    Node* last = list->info->last;
    Node* new;
    if(last == NULL){
        printf("error adding to list\n");
        exit(1);
    }

    new = (Node*)malloc(sizeof(Node));
    if(new == NULL){
        printf("error adding to list\n");
        exit(1);
    }

    new->value = newValue;
    new->info = list->info;
    new->next = NULL;
    new->prev = last;

    last->next = new;

    list->info->last=new;
    list->info->avg = ((list->info->avg*list->info->length)+newValue)/(list->info->length+1);
    list->info->length++;

}
void removeFromList(Node* toRemove){
    if(toRemove->next == NULL){
        toRemove->info->last = toRemove->prev;
        toRemove->prev->next = NULL;
    }
    else if(toRemove->prev == NULL){
        toRemove->info->first = toRemove->next;
        toRemove->next->prev = NULL;
    }
    else{
        toRemove->prev->next = toRemove->next;
        toRemove->next->prev = toRemove->prev;
    }

    toRemove->info->avg = ((toRemove->info->avg*toRemove->info->length)-toRemove->value)/(toRemove->info->length-1);
    toRemove->info->length--;

    /*in case the user removes the only Node left in the list*/
    if(toRemove->info->length == 0){
        free(toRemove);
    }
    free(toRemove);
}