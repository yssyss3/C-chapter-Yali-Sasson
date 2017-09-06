#ifndef LIST_LIBRARY_H
#define LIST_LIBRARY_H




struct Node{
    int value;
    struct ListInfo* info;

    struct Node* next;
    struct Node* prev;
};

struct ListInfo{
    int length;
    float avg;

    struct Node* first;
    struct Node* last;
};
typedef struct ListInfo ListInfo;

typedef struct Node Node;

Node* newList(int value);
void deleteList(Node* list);
void append(Node* list, int newValue);
void removeFromList(Node* toRemove);


#endif