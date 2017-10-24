#ifndef INT_LINKED_LIST
#define INT_LINKED_LIST
 
class SingleLinkedList
    {
    public:
        struct Node
            {
            int Info;
            Node    *Next;
            Node    (int i, Node * N = 0)
                {
                Info = i;
                Next = N;
                }
            };
 
        SingleLinkedList ()
            {
            Head = Tail = 0;
            }
 
        ~SingleLinkedList ();
        int     IsEmpty ()
            {
            return (Head == 0);
            }
        void    AddToHead       (int);
        void    AddToTail       (int);
        int     DeleteFromHead  ();
        bool    IsInList        (int) const;
 
    private:
        Node    *Head;
        Node    *Tail;
    };
 
#endif
