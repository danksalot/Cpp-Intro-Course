#include <iostream>
#include <string>

using namespace std;

#include "BinaryTree.h"

void main ()
	{
	BinaryTree <int>	BT;
	BinaryTree <string>	BT1;

	BT.Insert (5);
	BT.RecursiveInsert (4);

	BT1.RecursiveInsert ("abcd");
	}
