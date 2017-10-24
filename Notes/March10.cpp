#include <iostream>

using namespace std;

long	Add		(long, long);
long	Mult	(long, long);

void main ()
	{
	typedef long (* pFunc) (long, long);

	int		i;
	pFunc	FuncArray [2] = {Add, Mult};

	cout << "Which function do you want? ";
	cin >> i;
	switch (i)
		{
		case 0:
					cout << "Result is " << Add (3,5) << endl;
					break;
		case 1:
					cout << "Result is " << Add (3,5) << endl;
					break;
		}

	cout << "Which function do you want? ";
	cin >> i;
	cout << FuncArray [i] (3, 5) << endl;
	}

long Add (long a, long b)
	{
	return a + b;
	}

long Mult (long a, long b)
	{
	return a * b;
	}
