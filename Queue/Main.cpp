//////////////////////////////////////////////////////////
//                                                      //
//      Jacob Danks         2/17/2011                   //
//      Lab 2               COSC 2336.S70               //
//                                                      //
//////////////////////////////////////////////////////////
 
#include <iostream>
#include <WCS_String.h>
 
using namespace std;
 
#include "MyQueue.h"
 
void main ()
    {
    MyQueue <WCS_String> Q1;
    WCS_String Input;
    char Choice ('x');
    char LineFeed ('d');
 
    cout << "Welcome to Your Virtual Queue!" << endl;
    cout << "Here are the available commands:" << endl;
    cout << "Q YourStringHere - will place your string into the Queue" << endl;
    cout << "Enter D - will display the next item in your Queue" << endl;
    cout << "Enter X - will terminate the program" << endl;
    cout << "----------------------------------------------------------" << endl;
    do {
        cout << "Enter your Choice: ";
         
        cin.get (Choice);
        cin.get (LineFeed);
 
        switch (Choice)
            {
            case 'Q':
            case 'q':
                {
                Input.Read ();
                Q1.Queue (Input);
                break;
                }
            case 'D':
            case 'd':
                {
                if (Q1.Size () < 1)
                        cout << "Nothin in the Queue" << endl;
                    else
                        {
                        WCS_String Temp;
                        Q1.DeQueue (Temp);
                        Temp.Display ();
                        cout << endl;
                        }
                break;
                }
            case 'X':
            case 'x':
                break;
            default:
                {
                cout << "Please enter a valid command" << endl;
                }
            };
        }while ((Choice != 'X') && (Choice != 'x'));
    }
