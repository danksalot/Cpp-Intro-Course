#include "MathTree.h"
#include <iostream>
 
MathTree::Node::Node (const Token & T)
    {
    Toke    = T;
    pParent = 0;
    pLeft   = 0;
    pRight  = 0;
    }
 
MathTree::MathTree ()
    {
    pRoot = 0;
    pLastOperator = 0;
    }
 
MathTree::~MathTree ()
    {
    }
 
void MathTree::InsertOperand (const Token & T)
    {
    Node * pNode = new Node (T);
 
    if (!pRoot)
            pRoot = pNode;
        else
            {
            (*pLastOperator).pRight = pNode;
            (*pNode).pParent        = pLastOperator;
            }
    }
 
void MathTree::InsertBinaryOperator (const Token & T)
    {
    Node * pNode = new Node (T);
 
    while ((pLastOperator) && ((*pLastOperator).Toke.GetPrecedence () >= (*pNode).Toke.Precedence))
        pLastOperator = (*pLastOperator).pParent;
    if (pLastOperator)
            {
            (*pNode).pLeft              = (*pLastOperator).pRight;
            (*(*pNode).pLeft).pParent   = pNode;
            (*pNode).pParent            = pLastOperator;
            (*pLastOperator).pRight     = pNode;
            }
        else        // LastOperator is null
            {
            (*pRoot).pParent    = pNode;
            (*pNode).pLeft      = pRoot;
            pRoot               = pNode;
            }
    pLastOperator = pNode;
    }
 
void MathTree::InsertUnaryOperator (const Token & T)
    {
    Token Toke (Token::ConstantToken, 0);
    InsertOperand (Toke);
    InsertBinaryOperator (T);
    }
 
MathTree::Node * MathTree::GetLeftMostNode (Node * pNode)
    {
    while ((*pNode).pLeft)
            {
            (*pNode).Toke.IsLeftSideDone    = false;
            pNode                           = (*pNode).pLeft;
            }
    return pNode;
    }
 
Token::NumberType MathTree::Evaluate () // tree must be a valid tree or empty
    {
    Node * pNode;
 
    if (!pRoot)
            return 0;
        else
            {
            pNode = (*GetLeftMostNode (pRoot)).pParent;
            while (pNode != NULL)
                {
                if (!(*pNode).Toke.IsLeftSideDone)
                        {
                        (*pNode).Toke.Value             = GetValue ((*pNode).pLeft);//(*(*pNode).pLeft).Toke.GetValue ();
                        (*pNode).Toke.IsLeftSideDone    = true;
                        pNode                           = (*GetLeftMostNode ((*pNode).pRight)).pParent;
                        }
                    else
                        {
                        switch ((*pNode).Toke.Type)
                            {
                            case Token::OperatorPlusToken:
                                        (*pNode).Toke.Value += GetValue ((*pNode).pRight);
                                        break;
                            case Token::OperatorMinusToken:
                                        (*pNode).Toke.Value -= GetValue ((*pNode).pRight);
                                        break;
                            case Token::OperatorAsteriskToken:
                                        (*pNode).Toke.Value *= GetValue ((*pNode).pRight);
                                        break;
                            case Token::OperatorSlashToken:
                                        (*pNode).Toke.Value /= GetValue ((*pNode).pRight);
                                        break;
                            }
                        pNode = (*pNode).pParent;
                        }
                }
            return (*pRoot).Toke.Value;
            }
    }
 
void MathTree::DeleteTree ()
    {
    Node * pNode;
     
    if (pRoot)
            {
            pNode = (*GetLeftMostNode (pRoot)).pParent;
            while (pNode != NULL)
                {
                if (!(*pNode).Toke.IsLeftSideDone)
                        {
                        delete (*pNode).pLeft;
                        (*pNode).Toke.IsLeftSideDone    = true;
                        pNode                           = (*GetLeftMostNode ((*pNode).pRight)).pParent;
                        }
                    else
                        {
                        delete (*pNode).pRight;                 
                        pNode = (*pNode).pParent;
                        }
                }
            delete pRoot;
            pRoot = NULL;
            pLastOperator = NULL;
            }
        else;
    }
 
Token::NumberType MathTree::GetValue (Node * pNode)
    {
    if ((*pNode).Toke.Type == Token::VariableToken)
            if (Vars [(*pNode).Toke.Which].IsDefined)
                    return Vars [(*pNode).Toke.Which].Value;
                else
                    throw -1;
        else
            return (*pNode).Toke.Value;
    }
 
void MathTree::SetValue (int Which, Token::NumberType N)
    {
    Vars [Which].Value = N;
    Vars [Which].IsDefined = true;
    }
