#include <stdio.h>

#include "hashtable.h"

#define nStr 100

int main()
{
    struct hashtable* HashTable = hashtableCstr(HASHCONST);

    char * str1 = (char*) calloc (30, sizeof(*str1));
    
    printf ("Enter the str: \n");
    scanf  ("%[^\n]", str1);
  
    //printf ("%s", str1);

    add (HashTable, str1);
    add (HashTable, str1);
    add (HashTable, str1);

    printf("[%d]\n", find (HashTable, str1));
    printf("Frequences: <%d>\n", frequences (HashTable, str1));

    graphList (HashTable, hash (str1, HashTable));

    hashtableDstr (HashTable);
    free (str1);

    return 0;
}