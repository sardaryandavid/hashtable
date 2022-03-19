#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define POISON -17

struct node
{
    int data;
    
    char* str;

    struct node* next;
    struct node* prev;
};

struct list
{
    struct node* head;
    struct node* tail;

    size_t size;
};

//*******************************

void listCtor (list* List);

//*******************************

void listDstr (list* List);

//*******************************

void nodeDstr (node* Node);

//*******************************

struct node* newNode (int val);

//*******************************

void addNodeBefore (struct list* List, struct node* Node, struct node* newNode);

//*******************************

void addNodeAfter (struct list* List, struct node* Node, struct node* newNode);

//*******************************
void addHead (struct list* List, struct node* newNode);

//*******************************

void delNode (list* List, node* Node);

//*******************************

void listCtor (list* List)
{
    List->head = nullptr;
    List->tail = nullptr;

    List->size = 0;
}

//*******************************

struct node* newNode (int val, char* str)
{
    node* newNode = (struct node*) calloc(1, sizeof (*newNode));

    newNode->data = val;

    if (str != nullptr)
    {
        newNode->str = str;
    }

    newNode->next = nullptr;
    newNode->prev = nullptr;

    return newNode;
}

//*******************************

void addNodeBefore (struct list* List, struct node* Node, struct node* newNode)
{
    assert (Node != nullptr);
    assert (newNode != nullptr);

    newNode->next = Node;
    newNode->prev = Node->prev;

    Node->prev->next = newNode;
    Node->prev = newNode;    

    List->size++;
}

//*******************************

void addNodeAfter (struct list* List, struct node* Node, struct node* newNode)
{
    assert (Node != nullptr);
    assert (newNode != nullptr);

    addNodeBefore (List, Node->next, newNode);

    List->size++;
}

//*******************************

void addHead (struct list* List, struct node* newNode)
{
    assert (List != nullptr);
    assert (newNode != nullptr);

    if (List->size == 0)
    {
        List->head = newNode;
        List->tail = newNode;
    }

    else 
    {
        // перемещаем голову
        List->head->next = newNode;
        newNode->prev = List->head;
        List->head = newNode;

        newNode->next = nullptr;
    }

    List->size++;        
}

//*******************************

void delNode (list* List, node* Node)
{
    assert (List != nullptr);
    assert (List->size != 0);

    if (Node->next != nullptr)
    {
        if (Node->prev != nullptr)
        {
            Node->next->prev = Node->prev;
            Node->prev->next = Node->next;
        }

        else 
        {
            List->tail = Node->next;
            Node->next->prev = nullptr;
        }
    }

    else 
    {
        if (Node->prev != nullptr)
        {
            List->head = Node->prev;
            Node->prev->next = nullptr;
        }

        else 
        {
            List->head = nullptr;
            List->tail = nullptr;
        }
    
    }

    --List->size;

    Node->next = nullptr;
    Node->prev = nullptr;
    
    Node->data = POISON;

    free (Node); //нужно ли делать
}

#endif