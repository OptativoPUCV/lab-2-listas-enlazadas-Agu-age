#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List* list = (List*) malloc(sizeof(List));

    if(list == NULL) exit(1);
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
    return list;
}

void * firstList(List * list) {
    if(list == NULL || list->head == NULL) return NULL;
    list->current = list->head;
    return list->current->data;
}

void * nextList(List * list) {
    if(list == NULL || list->current == NULL || list->current->next == NULL) return NULL;

    list->current = list->current->next;
    
    return list->current->data;
}

void * lastList(List * list) {
    if(list == NULL || list->tail == NULL) return NULL;
    list->current = list->tail;
    return list->current->data;
}

void * prevList(List * list) {
    if(list == NULL || list->current == NULL || list->current->prev == NULL) return NULL;
    list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) {
    if(list == NULL) return;
    Node * newNode = createNode(data);
    if(newNode == NULL){
        return;
    }

    if(list->head == NULL){
        list->head = newNode;
        list->tail = newNode;
        return;
    }

    newNode->next = list->head;
    list->head->prev = newNode;
    list->head = newNode;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    if(list == NULL) return;

    if(list->head == NULL || list->current == NULL){
        pushFront(list, data);
        return;
    }
    Node* newNode = createNode(data);
    if(newNode == NULL) return;

    newNode->prev = list->current;
    newNode->next = list->current->next;

    if(list->current->next){
        list->current->next->prev = newNode;
    }
    else{
        list->tail = newNode;
    }
    list->current->next = newNode;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    if(list == NULL || list->current == NULL) return NULL;

    Node* aux = list->current;
    void* data = aux->data;

    Node* nextNode = aux->next;

    if(aux->prev == NULL){
        list->head = aux->next;
        if(list->head != NULL){
            list->head->prev = NULL;
        }
        else{
            list->tail = NULL;
        }
    }
    else{
        aux->prev->next = aux->next;
    }

    if(aux->next == NULL){
        list->tail = aux->prev;
    }
    else{
        aux->next->prev = aux->prev;
    }

    free(aux);
    list->current = nextNode;
    return data;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}