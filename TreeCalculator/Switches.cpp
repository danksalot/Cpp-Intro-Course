#include <iostream>
using namespace std;
#include "Switches.h"
#include "MathTree.h"

extern	MathTree MTree;
extern	char * Input;
extern	char Choice;
extern	Token::NumberType Number;
extern	int VarNumber;
extern	char Oper;
extern	int Precidence;
extern	char LineFeed;

void SwitchBeforeEval ()
	{
	cin.get (Choice);

			switch (Choice)
				{
				case 'c':
				case 'C':
					{
						cin >> Number;
						cin.get (LineFeed);
						//cout << "Constant Stored: " << Number << endl;
						Token T (Token::Constant, Number);
						MTree.InsertOperand (T);
						break;
					}
				case 'V':
					{
						cin >> VarNumber;
						cin.get (LineFeed);
						//cout << "Entering Variable " << VarNumber << endl;
						Token T (Token::Variable, 0);
						T.Type = Token::Variable;
						T.Which = VarNumber;
						MTree.InsertOperand (T);
						break;
					}
				case 'v':
					{
						cin >> VarNumber;
						cin >> Number;
						cin.get (LineFeed);
						MTree.SetValue (VarNumber, Number);
						//cout << "Variable " << VarNumber << " has been set to " << Number << endl;
						break;
					}
				case 'O':
				case 'o':
						{        
						cin.get (Oper);
						cin >> Precidence;
						if (Oper == '-')
								{
								Token Toke (Token::OperatorMinus, 0);
								Toke.Precedence = Token::AddSubtractPrecedence + Precidence;
								MTree.InsertBinaryOperator (Toke);
								}
							else 
								if (Oper == '+')
										{
										Token Toke (Token::OperatorPlus, 0);
										Toke.Precedence = Token::AddSubtractPrecedence + Precidence;
										MTree.InsertBinaryOperator (Toke);
										}
									else
										if (Oper == '*')
												{
												Token Toke (Token::OperatorMultiply, 0);
												Toke.Precedence = Token::MultDividePrecedence + Precidence;
												MTree.InsertBinaryOperator (Toke);
												}
											else
												if (Oper == '/')
														{
														Token Toke (Token::OperatorDivide, 0);
														Toke.Precedence = Token::MultDividePrecedence + Precidence;
														MTree.InsertBinaryOperator (Toke);
														}
													else
														if (Oper == '+')
																{
																Token Toke (Token::OperatorPlus, 0);
																Toke.Precedence = Token::UnaryPlusMinusPrecedence + Precidence;
																MTree.InsertUnaryOperator (Toke);
																}
															else
																if (Oper == '-')
																		{
																		Token Toke (Token::OperatorMinus, 0);
																		Toke.Precedence = Token::UnaryPlusMinusPrecedence + Precidence;
																		MTree.InsertUnaryOperator (Toke);
																		}
																	else
																		cout << "Not a valid Operator.  Try again." << endl;
						}
						cin.get (LineFeed);
						break;
				case 'E':
				case 'e':
						cout << MTree.Evaluate () << endl;
						cin.get (LineFeed);
						break;
				case 'D':
				case 'd':
						MTree.DeleteTree ();
						cin.get (LineFeed);
						break;
				case 'X':
				case 'x':
						exit (0);
						break;
				default:
						cout << "Invalid Input, try again" << endl;
						break;
				};
			cout << "Enter your next input" << endl;
	}
			
void SwitchAfterEval ()
	{	
	cin.get (Choice);

	switch (Choice)
		{
		case 'v':
			{
				cin >> VarNumber;
				cin >> Number;
				cin.get (LineFeed);
				MTree.SetValue (VarNumber, Number);
				//cout << "Variable " << VarNumber << " has been set to " << Number << endl;
				break;
			}
		case 'E':
		case 'e':
				cout << MTree.Evaluate () << endl;
				cin.get (LineFeed);
				break;
		case 'D':
		case 'd':
				MTree.DeleteTree ();
				cin.get (LineFeed);
				break;
		case 'X':
		case 'x':
				exit (0);
				break;
		default:
				cin.get (LineFeed);
				cout << "Invalid Input, try again" << endl;
				break;
		};
	cout << "Enter your next input" << endl;
	}
