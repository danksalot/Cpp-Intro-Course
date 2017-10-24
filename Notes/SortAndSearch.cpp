#include <iostream>

using namespace std;

#include <search.h>

int Compare (const void *, const void *);

void main ()
	{
	char X [] = "wkterzqtav";
	char Key;
	char * Location;

	cout << "Original string is " << X << endl;
	qsort (X, strlen (X), sizeof (char), Compare);
	cout << "Sorted string is   " << X << endl;
	Key = 'c';
	Location = (char *) bsearch (&Key, X, strlen (X), sizeof (char), Compare);
	if (Location != 0)
			cout << "Found " << Key << " at memory address " << (int *) Location << endl;
		else
			cout << Key << " Not Found" << endl;
	}

int Compare (const void * P1, const void * P2)
	{
	const char * pChar1 = (const char *) P1;
	const char * pChar2 = (const char *) P2;

	if (*pChar1 < *pChar2)
			return -1;
		else
			if (*pChar1 > *pChar2)
					return 1;
				else
					return 0;
	}
