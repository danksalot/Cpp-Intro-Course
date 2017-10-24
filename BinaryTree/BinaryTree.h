#ifndef BINARY_TREE_H
#define BINARY_TREE_H

template <class DATA>
	class BinaryTree
		{
		private:
			struct Node
				{
				Node *	pLeft;
				Node *	pRight;
				DATA	Data;

				Node (const DATA &);
				};
		public:
							BinaryTree		();
							~BinaryTree		();
			bool			Insert			(const DATA &);
			bool			RecursiveInsert	(const DATA &);
		private:
							BinaryTree	(const BinaryTree <DATA> &);
			BinaryTree &	operator =	(const BinaryTree <DATA> &);
			bool			LocalInsert	(const DATA &, Node *&);

			Node *	pRoot;
		};

template <class DATA>
	BinaryTree <DATA>::Node::Node (const DATA & D)
		{
		Data	= D;
		pLeft	= 0;
		pRight	= 0;
		}

template <class DATA>
	BinaryTree <DATA>::BinaryTree ()
		{
		pRoot = 0;
		}

template <class DATA>
	BinaryTree <DATA>::~BinaryTree ()
		{
		}

template <class DATA>
	bool BinaryTree <DATA>::Insert (const DATA & D)
		{
		if (!pRoot)
				{
				pRoot = new Node (D);
				return true;
				}
			else
				{
				Node * pNode = pRoot;
				for (;;)
					if ((*pNode).Data == D)
							return false;
						else
							if ((*pNode).Data < D)
									if ((*pNode).pRight)
											pNode = (*pNode).pRight;
										else
											{
											(*pNode).pRight = new Node (D);
											return true;
											}
								else
									if ((*pNode).pLeft)
											pNode = (*pNode).pLeft;
										else
											{
											(*pNode).pLeft = new Node (D);
											return true;
											}
			}
		}

template <class DATA>
	inline bool BinaryTree <DATA>::RecursiveInsert (const DATA & D)
		{
		return LocalInsert (D, pRoot);
		}

template <class DATA>
	bool BinaryTree <DATA>::LocalInsert (const DATA & D, Node * & pNode)
		{
		if (!pNode)
				{
				pNode = new Node (D);
				return true;
				}
			else
				if ((*pNode).Data == D)
						return false;
					else
						if ((*pNode).Data < D)
								return LocalInsert (D, (*pNode).pRight);
							else
								return LocalInsert (D, (*pNode).pLeft);
		}

#endif
