//#define Debugging		// comment out when not debugging

#include <iostream>

using namespace std;

#include <ctype.h>
#include <stdarg.h>		// for the va_ stuff used below
#include <stdlib.h>		// for printf and related functions

// char * printf (const char *, ...);	// old style way of doing output
// char * scanf (const char *, ...);	// old style way of doing input
// char * sprintf (char *, const char *, ...);	// formats a string for output like printf does and then copies it to where the first parameter points

int Sum (int, ...);

#define Add(a,b)	((a) + (b))
#define Mult(a,b)	((a) * (b))
#define IsDigit(c)	(((c) >= '0') && ((c) <= '9'))
#define Display(c)	cout << #c << " has the value " << c << endl
#define Display2(a,b,c)	cout << "The name is " << a##b##c << endl

#ifdef  Debugging
#define Debug(x)	\
	cout << #x << " has the value " << x << " on line " << __LINE__ << " in file " << __FILE__ << endl
#else
#define Debug(x)
#endif


void main (int argc, char * argv [], char * envp [])
	{
	int		I1 (113);
	char	C1 ('X');
	char	C2 [] = "wxyz";
	cout << "First Sum is  " << Sum (4, 1, 2, 3, 4) << endl;
	cout << "Second Sum is " << Sum (0) << endl;
	cout << "Third Sum is  " << Sum (9, 1, 2, 3, 4, 5, 6, 7, 8, 9) << endl;

	printf ("Values are %d, %c, %s\n", I1, C1, C2);

	Debug (I1);

	int x (8);
	int y (5);

	cout << "Add yields    " << Add (x, y) << endl;
	cout << "Now it yields " << Add (x, y) * 2 << endl;
	cout << "Mult yields   " << Mult (x, y) << endl;
	cout << "Now it yields " << Mult (x + 2, y) << endl;

	Display (x + y);
	Display2 ("Bill", " ", "Slater");

	cout << "Enter a character: ";
	if (IsDigit (cin.get ()))
			cout << "Is a digit" << endl;
		else
			cout << "Is NOT a digit" << endl;
	cout << "Enter a character: ";
	if (isdigit (cin.get ()))
			cout << "Is a digit" << endl;
		else
			cout << "Is NOT a digit" << endl;
	}

int Sum (int NumParameters, ...)
	{
	int			Total (0);
	int			i;
	va_list		ArgPtr;						// will be pointer to the parameter list
	va_start	(ArgPtr, NumParameters);	// point to first parameter

	// sum up the total of the values of the parameters
	for (i = 0; i < NumParameters; i++)
		Total += va_arg (ArgPtr, int);	// sets ArgPtr to point to next parameter and get its value
	return Total;
	}
