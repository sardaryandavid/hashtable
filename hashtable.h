#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "ptrList.h"
#include "graphviz.h"
#include <cstring>

#define HASHCONST 111017

enum ans {NO, YES};

#define ERROR -1

//*********************************

struct hashtable 
{
    node** arrOfLists; // массив списков (сама хеш-таблица)

    size_t size;       // максимальный размер хеш-таблицы
    size_t currSize;   // текущий размер
};

//*********************************

unsigned int hash(char* str, struct hashtable* HashTable);

//*********************************

struct hashtable*  hashtableCstr (size_t size);

//*********************************

void hashtableDstr (hashtable* HashTable);

//*********************************

unsigned int hash(char* str, struct hashtable* HashTable)
{
    assert (str != nullptr);
    assert (HashTable != nullptr);

    int hashRes = 0;

    int strSize = strlen (str);

    for (int i = 0; i < strSize; ++i)
    {
        hashRes = (HASHCONST * hashRes + (int)(*(str + i))) % HashTable->size;
    }

    hashRes = (hashRes * hashRes);

    return hashRes % HashTable->size;
}

//*********************************

struct hashtable*  hashtableCstr (size_t size)
{
    struct hashtable* HashTable = (hashtable*) calloc (1, sizeof(*HashTable));

    HashTable->arrOfLists = (node**) calloc (size, sizeof(*HashTable->arrOfLists));

    HashTable->size = size;
    HashTable->currSize = 0;

    return HashTable;
}

//*********************************

void hashtableDstr (hashtable* HashTable)
{
    assert (HashTable != nullptr);

    for (int i = 0; i < HashTable->size; ++i)
    {
        if (*(HashTable->arrOfLists + i) != nullptr)
        {
            node* currNode = *(HashTable->arrOfLists + i);

            if (currNode->next == nullptr)
                free (currNode);
            
            else
            {
                node* nextNode = (*(HashTable->arrOfLists + i))->next;

                while (nextNode != nullptr)
                {
                    free (currNode);

                    currNode = nextNode;
                    nextNode = currNode->next;
                }

                free (currNode);
            }
            
        }
    }
    
    free (HashTable->arrOfLists);
    free (HashTable);
}

//*********************************

int equalStr (char* str1, char* str2)
{
    assert (str1 != nullptr);
    assert (str2 != nullptr);

    return !strcmp (str1, str2);
}

int repeatInTable (hashtable* HashTable, char* str)
{
    assert (HashTable != nullptr);
    assert (str != nullptr);

    int hashVal = hash (str, HashTable);

    if (equalStr((*(HashTable->arrOfLists + hashVal))->str, str))
    {
        (*(HashTable->arrOfLists + hashVal))->freq += 1;
        return 1;
    }

    return 0;
}
void add (hashtable* HashTable, char* str)
{
    assert (HashTable != nullptr);
    assert (str != nullptr);

    int hashVal = hash (str, HashTable);

    if (*(HashTable->arrOfLists + hashVal) == nullptr)
    {
        node* NewNode = newNode (str);

        *(HashTable->arrOfLists + hashVal) = NewNode;
        ++HashTable->currSize;
    }

    else
    {   
        int wasRepeat = repeatInTable (HashTable, str);

        if (wasRepeat == 0)
        {
            while ((*(HashTable->arrOfLists + hashVal))->next != nullptr)
            {
                (*(HashTable->arrOfLists + hashVal)) = (*(HashTable->arrOfLists + hashVal))->next;

                wasRepeat = repeatInTable (HashTable, str);

                if (wasRepeat)
                    break;
            }
        }

        if (!wasRepeat)
        {
            node* NewNode = newNode (str);

            (*(HashTable->arrOfLists + hashVal))->next = NewNode;
            ++HashTable->currSize;
        }
    }
}

//*********************************

int find (hashtable* HashTable, char* str)
{
    assert (HashTable != nullptr);

    int hashVal = hash(str, HashTable);

    if (*(HashTable->arrOfLists + hashVal) != nullptr && 
        strcmp((*(HashTable->arrOfLists + hashVal))->str, str) == 0)
            return YES;

    return NO;
}

int frequences (hashtable* HashTable, char* str)
{
    assert (HashTable != nullptr);

    int hashVal = hash(str, HashTable);

    if (*(HashTable->arrOfLists + hashVal) != nullptr && 
        strcmp((*(HashTable->arrOfLists + hashVal))->str, str) == 0)
            return (*(HashTable->arrOfLists + hashVal))->freq;

    return ERROR;
}

void graphHashTable (hashtable* HashTable)
{
    assert (HashTable);

    return;
}

void graphList (hashtable* HashTable, int hashVal)
{
    assert (HashTable != nullptr);

    FILE* graphfile = fopen ("graph.txt", "w");

    grBegin(graphfile);

    if (*(HashTable->arrOfLists + hashVal) != nullptr)
    {
        node* currNode = *(HashTable->arrOfLists + hashVal);

        if (currNode->next == nullptr)
        {
            addNode (graphfile, currNode);
        }
        
        else 
        {
            node* nextNode = (*(HashTable->arrOfLists + hashVal))->next;

            while (nextNode != nullptr)
            {
                addNode (graphfile, currNode);

                currNode = nextNode;
                nextNode = currNode->next;
            }

            addNode (graphfile, currNode);
        }
    }

    fprintf (graphfile, "   edge[color=\"darkgreen\",fontcolor=\"blue\",fontsize=12];\n");

    grEnd (graphfile);

    fclose (graphfile);
}


#endif 