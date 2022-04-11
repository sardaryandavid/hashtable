#ifndef GRAPHVIZ_H
#define GRAPHVIZ_H

#include <stdio.h>
#include "ptrList.h"

void grBegin (FILE* graphfile)
{
    fprintf (graphfile, "digraph G{\n");
}

void grInf (FILE* graphfile, list* List)
{
     fprintf(graphfile, 
                    "   first [shape=record,label=\"  list tail\\n %p | list head\\n %p | list size\\n %ld\" ];\n", 
                    List->tail, List->head, List->size);
}

void addNode (FILE* graphfile, node* Node)
{
    fprintf(graphfile, "   List%p  [shape = record, label = \"<a%p> address\\n %p | str %s | <f%p> next | <ff%p> prev\"];\n", 
                               Node, Node, Node, Node->str, Node, Node);
}

void grRel (FILE* graphfile, list* List)
{
    int i = 0;
    struct node* NodeI = List->tail;

    fprintf (graphfile, "   edge[color=\"darkgreen\",fontcolor=\"blue\",fontsize=12];\n");

    while (i++ < List->size)
    {
        if (NodeI != nullptr && NodeI != List->head)
        {
            fprintf (graphfile, "   List%p:  <f%p>  -> List%p: <a%p>;\n", 
                                     NodeI, NodeI, NodeI->next, NodeI->next);
            NodeI = NodeI->next;
        }
    }

    fprintf (graphfile, "   edge[color=\"darkblue\",fontcolor=\"blue\",fontsize=12];\n");

    i = 0;
    struct node* NodeP = List->head;

    while (i++ < List->size)
    {
        if (NodeP->prev != nullptr && NodeP != List->tail)
        {
            fprintf (graphfile, "   List%p:  <ff%p>  -> List%p: <a%p>;\n", 
                                 NodeP, NodeP, NodeP->prev, NodeP->prev);
            NodeP = NodeP->prev;
        }
    }
}

void grEnd (FILE* graphfile) 
{
    assert (graphfile != nullptr);

    fprintf (graphfile, "}");
}

void listGraph (FILE* graphfile, list* List)
{
    assert (List != nullptr);
    assert (graphfile != nullptr);
    
    grBegin (graphfile);
    grInf   (graphfile, List);

    struct node* NodeI = List->tail; 

    int i = 0;

    while (i++ < List->size)
    {
        addNode (graphfile, NodeI);
        
        NodeI = NodeI->next;
    }

    grRel (graphfile, List);
    grEnd   (graphfile);
}

#endif 