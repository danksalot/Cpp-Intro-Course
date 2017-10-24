#include <iostream>
#include <WCS_String.h>
 
using namespace std;
 
#include "Statement.h"
 
void main (int argc, char * argv [])
    {
    WCS_String Temp;
    Statement S1;
 
    if (argc < 2)
        {
        Temp = "Test.txt";
        }
    else
        Temp = argv [1];
 
    S1.OpenFile(Temp);
 
    do  {
        S1.Build ();
    } while (S1.GetType () != Statement::EndOfInput);
 
    S1.CloseFile();
    }
