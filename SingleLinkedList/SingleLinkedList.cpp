#include <iostream>
#include "SingleLinkedList.h"
 
SingleLinkedList::~SingleLinkedList ()
    {
    for (Node *p; !IsEmpty (); )
        {
        p = (*Head).Next;
        delete Head;
        Head = p;
        }
    }
 
void SingleLinkedList::AddToHead (int I)
    {
    Head = new Node (I, Head);
    if (Tail == 0)
        Tail = Head;
    }
 
void SingleLinkedList::AddToTail (int I)
    {
    if (Tail == 0)
            {
            (*Tail).Next = new Node (I);
            Tail = (*Tail).Next;
            }
        else
            Head = Tail = new Node (I);
    }
 
int SingleLinkedList::DeleteFromHead ()
    {
    int     i       = (*Head).Info;
    Node    *temp   = Head;
    if (Head == Tail)
            Head = Tail = 0;
        else
            Head = (*Head).Next;
    delete temp;
    return i;
    }
 
bool SingleLinkedList::IsInList (int I) const
    {
    Node *temp;
    for (temp = Head; (temp != 0 && !((*temp).Info == I)); temp = (*temp).Next);
    return (temp != 0);
    }
