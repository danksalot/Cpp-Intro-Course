#ifndef MYUBARRAY_H
#define MYUBARRAY_H
 
//#include <WCS_Pointer.h>
//#include <WCS_String.h>
#include <wcsplugin.h>
 
enum Exception {NoList, NoCurrent, NoNextElement, NoPreviousElement, IndexNotFound};
 
template <class DATA, class INDEX>
    class UBArray
        {   
        private:
            struct Node: public RefCount
                {
                Node    (const INDEX &);
 
                DATA    Data;
                INDEX   Index;
                WCS_Pointer <Node>    pNext;
                WCS_Pointer <Node>    pPrev;
                };
        public:
                            UBArray     ();
                            ~UBArray    ();
                    void    ClearAll    ();
                    DATA &  GetFirst    ();
                    DATA &  GetLast     ();
                    DATA &  GetNext     ();
                    DATA &  GetPrev     ();
            const   DATA &  GetFirst    () const;
            const   DATA &  GetLast     () const;
            const   DATA &  GetNext     () const;
            const   DATA &  GetPrev     () const;
                    bool    Remove      (const INDEX &);
                    size_t  Size        () const;
                    DATA &  operator [] (const INDEX &);
            const   DATA &  operator [] (const INDEX &) const;
                    DATA &  At          (const INDEX &);
            const   DATA &  At          (const INDEX &) const;
        private:
                    UBArray     (const UBArray <DATA, INDEX> &);
            void    operator =  (const UBArray <DATA, INDEX> &);
 
                    WCS_Pointer <Node>    pHead;
                    WCS_Pointer <Node>    pTail;
            mutable WCS_Pointer <Node>    pCurrent;
                    size_t              NumNodes;
        };
 
    //CONSTRUCTORS AND DECONSTRUCTORS
template <class DATA, class INDEX>
    UBArray <DATA, INDEX>::Node::Node (const INDEX & I): Index (I)
        {
        }
 
template <class DATA, class INDEX>
    UBArray <DATA, INDEX>::UBArray ()
        {
        NumNodes = 0;
        }
 
template <class DATA, class INDEX>
    UBArray <DATA, INDEX>::~UBArray ()
        {
        ClearAll ();
        }
 
    //OVERLOADED OPERATORS
template <class DATA, class INDEX>
    DATA & UBArray <DATA, INDEX>::operator [] (const INDEX & I)
        {
        WCS_Pointer <Node>    pNode;
        if (!pHead.Exists ())
                {
                pHead   = WCS_Pointer <Node> (new Node (I));
                NumNodes++;
                pTail   = pHead;
                return (*pHead).Data;
                }
            else
                if (I < (*pHead).Index)
                        {
                        pNode           = WCS_Pointer <Node> (new Node (I));
                        NumNodes++;
                        (*pNode).pNext  = pHead;
                        (*pHead).pPrev  = pNode;
                        pHead           = pNode;
                        return (*pNode).Data;
                        }
                    else
                        if (I == (*pHead).Index)
                                return (*pHead).Data;
                            else
                                if (I > (*pTail).Index)
                                        {
                                        pNode           = WCS_Pointer <Node> (new Node (I));
                                        NumNodes++;
                                        (*pNode).pPrev  = pTail;
                                        (*pTail).pNext  = pNode;
                                        pTail           = pNode;
                                        return (*pNode).Data;
                                        }
                                    else
                                        if (I == (*pTail).Index)
                                                return (*pTail).Data;
                                            else
                                                {
                                                WCS_Pointer <Node>    pTemp ((*pHead).pNext);
                                                while (I > (*pTemp).Index)
                                                    pTemp = (*pTemp).pNext;
                                                if (I == (*pTemp).Index)
                                                        return (*pTemp).Data;
                                                    else
                                                        {
                                                        pNode                   = WCS_Pointer <Node> (new Node (I));
                                                        NumNodes++;
                                                        (*pNode).pNext          = pTemp;
                                                        (*pNode).pPrev          = (*pTemp).pPrev;
                                                        (*pTemp).pPrev          = pNode;
                                                        (*(*pNode).pPrev).pNext = pNode;
                                                        return (*pNode).Data;
                                                        }
                                                }
        }
 
template <class DATA, class INDEX>
    const DATA & UBArray <DATA, INDEX>::operator [] (const INDEX & I) const
        {
        WCS_Pointer <Node>    pNode;
        if (!pHead.Exists ())
                throw (NoList);
            else
                if (I < (*pHead).Index)
                        throw (IndexNotFound);
                    else
                        if (I == (*pHead).Index)
                                return (*pHead).Data;
                            else
                                if (I > (*pTail).Index)
                                        throw (IndexNotFound);
                                    else
                                        if (I == (*pTail).Index)
                                                return (*pTail).Data;
                                            else
                                                {
                                                WCS_Pointer <Node>    pTemp ((*pHead).pNext);
                                                while (I > (*pTemp).Index)
                                                    pTemp = (*pTemp).pNext;
                                                if (I == (*pTemp).Index)
                                                        return (*pTemp).Data;
                                                    else
                                                        throw (IndexNotFound);
                                                }
        }
 
    //METHODS
template <class DATA, class INDEX>
    inline size_t UBArray <DATA, INDEX>::Size () const
        {
        return NumNodes;
        }
 
template <class DATA, class INDEX>
    void UBArray <DATA, INDEX>::ClearAll ()
        {
        if (pHead.Exists ())
            {
            pTail.SetToNull ();
 
            while (((pHead) != NULL) && ((*pHead).pNext != NULL)) 
                {
                pHead = (*pHead).pNext;
                (*pHead).pPrev.SetToNull ();
                }
            pHead.SetToNull ();
                NumNodes = 0;
            }
        }
 
template <class DATA, class INDEX>
    DATA & UBArray <DATA, INDEX>::At (const INDEX & I)
        {
        return (*this) [I];
        }
 
template <class DATA, class INDEX>
    const DATA & UBArray <DATA, INDEX>::At (const INDEX & I) const
        {
        return (*this) [I];
        }
 
template <class DATA, class INDEX>
    bool UBArray <DATA, INDEX>::Remove (const INDEX & I)
    {
    if (!pHead.Exists ())
            return false;
        else
            if (I < (*pHead).Index)
                    return false;
                else
                    if (I == (*pHead).Index)
                            {
                            pHead = (*pHead).pNext;
                            if (pHead == 0)
                                pTail.SetToNull ();
                            else
                                (*pHead).pPrev.SetToNull ();
                            NumNodes--;
                            return true;
                            }
                        else
                            if (I == (*pTail).Index)
                                    {
                                    pTail = (*pTail).pPrev;
                                    if (pTail == NULL)
                                        pHead.SetToNull ();
                                    else
                                        (*pTail).pNext.SetToNull ();
                                    NumNodes--;
                                    return true;
                                    }
                                else
                                    if (I > (*pTail).Index)
                                            return false;
                                        else
                                            {
                                            WCS_Pointer <Node>    pTemp ((*pHead).pNext);
                                            while (I > (*pTemp).Index)
                                                pTemp = (*pTemp).pNext;
                                            if (I == (*pTemp).Index)
                                                    {
                                                    (*(*pTemp).pNext).pPrev = (*pTemp).pPrev;
                                                    (*(*pTemp).pPrev).pNext = (*pTemp).pNext;
                                                    pTemp.SetToNull ();
                                                    NumNodes--;
                                                    return true;
                                                    }
                                                else
                                                    return false;
                                    }
 
        }
 
    //ITERATORS
template <class DATA, class INDEX>
    DATA & UBArray <DATA, INDEX>::GetFirst ()
        {
        pCurrent = pHead;
        if (pCurrent.Exists ())
                return (*pCurrent).Data;
            else
                throw NoList;
        }
     
template <class DATA, class INDEX>
    DATA & UBArray <DATA, INDEX>::GetNext ()
        {
        if (pHead.Exists ())
                if (pCurrent.Exists ())
                        if ((*pCurrent).pNext.Exists ())
                                {
                                pCurrent = (*pCurrent).pNext;
                                return (*pCurrent).Data;
                                }
                            else
                                throw NoNextElement;
                    else
                        throw NoCurrent;
            else
                throw NoList;
        }
 
template <class DATA, class INDEX>
    DATA & UBArray <DATA, INDEX>::GetLast ()
        {
        pCurrent = pTail;
        if (pCurrent.Exists ())
                return (*pCurrent).Data;
            else
                throw NoList;
        }
     
template <class DATA, class INDEX>
    DATA & UBArray <DATA, INDEX>::GetPrev ()
        {
        if (pHead.Exists ())
                if (pCurrent.Exists ())
                        if ((*pCurrent).pPrev.Exists ())
                                {
                                pCurrent = (*pCurrent).pPrev;
                                return (*pCurrent).Data;
                                }
                            else
                                throw NoPreviousElement;
                    else
                        throw NoCurrent;
            else
                throw NoList;
        }
 
template <class DATA, class INDEX>
    const DATA & UBArray <DATA, INDEX>::GetFirst () const
        {
        pCurrent = pHead;
        if (pCurrent.Exists ())
                return (*pCurrent).Data;
            else
                throw (NoList);
        }
     
template <class DATA, class INDEX>
    const DATA & UBArray <DATA, INDEX>::GetNext () const
        {
            if (pHead.Exists ())
                    if (pCurrent.Exists ())
                            if ((*pCurrent).pNext.Exists ())
                                    {
                                    pCurrent = (*pCurrent).pNext;
                                    return (*pCurrent).Data;
                                    }
                                else
                                    throw NoNextElement;
                        else
                            throw NoCurrent;
                else
                    throw NoList;
        }
 
template <class DATA, class INDEX>
    const DATA & UBArray <DATA, INDEX>::GetLast () const
        {
        pCurrent = pTail;
        if (pCurrent.Exists ())
                return (*pCurrent).Data;
            else
                throw NoList;
        }
     
template <class DATA, class INDEX>
    const DATA & UBArray <DATA, INDEX>::GetPrev () const
        {
        if (pHead.Exists ())
                if (pCurrent.Exists ())
                        if ((*pCurrent).pPrev.Exists ())
                                {
                                pCurrent = (*pCurrent).pPrev;
                                return (*pCurrent).Data;
                                }
                            else
                                throw NoPreviousElement;
                    else
                        throw NoCurrent;
            else
                throw NoList;
        }
#endif
