#include "MathTree.h"

MathTree::Node::Node (const Token & T)
	{
	Toke	= T;
	pParent	= 0;
	pLeft	= 0;
	pRight	= 0;
	}

MathTree::MathTree ()
	{
	pRoot = 0;
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
			(*pNode).pParent		= pLastOperator;
			}
	}

void MathTree::InsertBinaryOperator (const Token & T)
	{
	Node * pNode = new Node (T);

	while (pLastOperator && ((*pLastOperator).Toke.Precedence >= (*pNode).Toke.Precedence))
		pLastOperator = (*pLastOperator).pParent;
	if (pLastOperator)
			{
			(*pNode).pLeft				= (*pLastOperator).pRight;
			(*(*pNode).pLeft).pParent	= pNode;
			(*pNode).pParent			= pLastOperator;
			(*pLastOperator).pRight		= pNode;
			}
		else		// LastOperator is null
			{
			(*pRoot).pParent	= pNode;
			(*pNode).pLeft		= pRoot;
			pRoot				= pNode;
			}
	pLastOperator = pNode;
	}

void MathTree::InsertUnaryOperator (const Token & T)
	{
	Token Toke (Token::Constant, 0);
	InsertOperand (Toke);
	InsertBinaryOperator (T);
	}

MathTree::Node * MathTree::GetLeftMostNode (Node * pNode)
	{
	while ((*pNode).pLeft)
			{
			(*pNode).Toke.IsLeftSideDone	= false;
			pNode							= (*pNode).pLeft;
			}
	return pNode;
	}

Token::NumberType MathTree::Evaluate ()	// tree must be a valid tree or empty
	{
	Node * pNode;

	if (!pRoot)
			return 0;
		else
			{
			pNode = (*GetLeftMostNode (pRoot)).pParent;
			while (pNode)
				{
				if (!(*pNode).Toke.IsLeftSideDone)
						{
						(*pNode).Toke.Value				= (*(*pNode).pLeft).Toke.Value;
						(*pNode).Toke.IsLeftSideDone	= true;
						pNode							= (*GetLeftMostNode ((*pNode).pRight)).pParent;
						}
					else
						{
						switch ((*pNode).Toke.Type)
							{
							case Token::OperatorPlus:
										(*pNode).Toke.Value += GetValue ((*pNode).pRight);
										break;
							case Token::OperatorMinus:
							case Token::OperatorMultiply:
							case Token::OperatorDivide:
								;
							}
						pNode = (*pNode).pParent;
						}
				}
			return (*pRoot).Toke.Value;
			}
	}

Token::NumberType MathTree::GetValue (Node * pNode)
	{
	if ((*pNode).Toke.Type == Token::Variable)
			if (Vars [(*pNode).Toke.Which].IsDefined)
					return Vars [(*pNode).Toke.Which].Value;
				else
					throw -1;
		else
			return (*pNode).Toke.Value;
	}
