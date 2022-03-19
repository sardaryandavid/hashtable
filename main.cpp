#include <stdio.h>

#include "hashtable.h"

#define nStr 100

int main()
{
    struct hashtable* HashTable = hashtableCstr(20);

    char * str1 = (char*) calloc (20, sizeof(*str1));
    
    printf ("Enter the str: ");
    scanf  ("%s", str1);
    printf ("%s", str1);

    add (HashTable, str1);
    printf("\n[%s]", find (HashTable, hash(str1, HashTable)));

    hashtableDstr (HashTable);

    free (str1);

    return 0;
}