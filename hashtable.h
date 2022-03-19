#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "ptrList.h"
#include <cstring>

#define HASHCONST 117

//*********************************

struct hashtable 
{
    node** arrOfLists; // массив списков (сама хеш-таблица)

    size_t size;       // ее размер
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
            {
                free (currNode);
            }
            
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

void add (hashtable* HashTable, char* str)
{
    assert (HashTable != nullptr);
    assert (str != nullptr);

    int hashVal = hash(str, HashTable);

    node* NewNode = newNode (hashVal, str);

    if (*(HashTable->arrOfLists + hashVal) == nullptr)
    {
        *(HashTable->arrOfLists + hashVal) = NewNode;
    }

    else
    {
        (*(HashTable->arrOfLists + hashVal))->next =  NewNode;
    }
}

//*********************************

// функция find возвращает первую найденную строчку по данному хешу (если такая есть)

char* find (hashtable* HashTable, int hashVal)
{
    assert (HashTable != nullptr);

    if (*(HashTable->arrOfLists + hashVal) != nullptr)
    {
        return (*(HashTable->arrOfLists + hashVal))->str;
    }    

    return nullptr;
}


#endif 