#include <iostream>

using namespace std;

#include "MemoryPool.h"

class TreeNode
	{
	public:
		void CleanUp ()
			{
			Left.SetToNull ();
			Right.SetToNull ();
			Parent.SetToNull ();
			}
		void Init (const TreeNode &) {}
		void Init () {}
		int a;
	private:
		POOL_POINTER (TreeNode) Left;
		POOL_POINTER (TreeNode) Right;
		POOL_POINTER (TreeNode) Parent;
	};

void main ()
	{
	TreeNode TR;
	MemoryPool <TreeNode> M (50);
	POOL_POINTER (TreeNode) N = M.GetMemoryBlock (TR);
	POOL_POINTER (TreeNode) X = M.GetMemoryBlock ();
	X.SetToNull ();
	(*N).a = 5;
	cout << (*N).a << endl;
	M.FreeMemoryBlock (N);
	}
