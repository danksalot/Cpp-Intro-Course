#ifndef MYQUEUE_H
#define MYQUEUE_H
 
#include <MyUBArray.h>
 
template <class DATA>
    class MyQueue: private UBArray <DATA, size_t>
    {
    public:
                    MyQueue     ();
                    ~MyQueue    ();
        size_t      Size        ();
        bool        Queue       (const DATA &);
        bool        DeQueue     (DATA &);
    private:
                    MyQueue     (const MyQueue <DATA> &);
        MyQueue &   operator =  (const MyQueue <DATA> &);
        size_t      Count;
    };
 
template <class DATA>
    MyQueue <DATA>::MyQueue (): Count (0)
        {
        }
 
template <class DATA>
    MyQueue <DATA>::~MyQueue ()
        {
        }
 
template <class DATA>
    size_t MyQueue <DATA>::Size ()
        {
        return Count;
        }
 
template <class DATA>
    bool MyQueue <DATA>::Queue (const DATA & D)
        {
        (*this) [Count++] = D;
        return true;
        }
 
template <class DATA>
    bool MyQueue <DATA>::DeQueue (DATA & D)
        {
        if (Count > 0)
                {
                D = (*this) [0];
                for (int i = 0; i < Count-1; i++)
                    (*this) [i] = (*this) [i+1];
                Count--;
                return true;
                }
            else
                return false;
        }
 
#endif
