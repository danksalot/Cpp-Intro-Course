//////////////////////////////////////
//									//
//	Jacob Danks		03/31/2011		//
//	Lab Four		COSC 2336.S70	//
//									//
//////////////////////////////////////

#include <iostream>

using namespace std;

#include "MathTree.h"
#include "Switches.h"

//VARIABLES
	MathTree MTree;
	char * Input ("ThisHadBetterBeLongEnough");
	char Choice ('f');
	Token::NumberType Number (0);
	int VarNumber (0);
	char Oper ('f');
	int Precidence (0);
	char LineFeed ('j');

void main ()
	{

	cout << "Welcome to the Tree Calculator" << endl;
	cout << "Enter your Data Now" << endl;
	
	do
		{
		do
			{
			SwitchBeforeEval ();
			}while ((Choice != 'E') && (Choice != 'e'));
		do
			{
			SwitchAfterEval ();
			}while (!((Choice == 'D') || (Choice == 'd')));
		}while ((Choice == 'D') || (Choice == 'd'));
	}
