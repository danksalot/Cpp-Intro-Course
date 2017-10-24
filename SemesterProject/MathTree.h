#ifndef MATH_TREE_H
#define MATH_TREE_H
 
#include "Token.h"
 
class MathTree
    {
    public:
        struct Node
            {
            Node        (const Token &);
 
            Token   Toke;
            Node *      pParent;
            Node *      pLeft;
            Node *      pRight;
            };
        struct Variable
            {
            Token::NumberType   Value;
            bool                    IsDefined;
            };
 
                                MathTree                ();
                                ~MathTree               ();
        void                    InsertOperand           (const Token &);
        void                    InsertBinaryOperator    (const Token &);
        void                    InsertUnaryOperator     (const Token &);
        Node *                  GetLeftMostNode         (Node *);
        Token::NumberType   GetValue                (Node *);
        void                    SetValue                (int, Token::NumberType);
        Token::NumberType   Evaluate                ();
        void                    DeleteTree              ();
    private:
                    MathTree    (const MathTree &);
        MathTree &  operator =  (const MathTree &);
 
        Node *      pRoot;
        Node *      pLastOperator;
        Variable    Vars [100];
 
    };
 
#endif
