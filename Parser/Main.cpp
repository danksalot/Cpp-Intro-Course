//**************************************//
//                                      //
//      Jacob Danks         4/14/11     //
//      COSC 2336.S70       Lab 5       //
//                                      //
//**************************************//
 
#include "Token.h"
 
void main (int argc, char * argv [])
    {
    WCS_String Temp;
    Token Toke;
 
    if (argc < 2)
            {
            cout << "Reading tokens from keyboard" << endl;
            Temp = "KEYBOARD";
            }
        else
            Temp = argv [1];
    Token::OpenFile (Temp);
    do  {
        Toke.Build ();
        switch (Toke.GetType ())
            {
            case Token::KeywordEvalToken:
                cout << "Found Keyword EVAL" << endl;
                break;
            case Token::KeywordValueToken:
                cout << "Found Keyword VALUE" << endl;
                break;
            case Token::KeywordExpToken:
                cout << "Found Keyword EXP" << endl;
                break;
            case Token::VariableToken:
                cout << "Found Variable Token" << endl;
                break;
            case Token::ConstantToken:
                cout << "Found Constant Token" << endl;
                break;
            case Token::OperatorPlusToken:
                cout << "Found Plus Operator" << endl;
                break;
            case Token::OperatorMinusToken:
                cout << "Found Minus Operator" << endl;
                break;
            case Token::OperatorAsteriskToken:
                cout << "Found Asterisk Operator" << endl;
                break;
            case Token::OperatorSlashToken:
                cout << "Found Slash Operator" << endl;
                break;
            case Token::SymbolOpenParenToken:
                cout << "Found Symbol '('" << endl;
                break;
            case Token::SymbolCloseParenToken:
                cout << "Found Symbol ')'" << endl;
                break;
            case Token::SymbolSemiColonToken:
                cout << "Found Symbol ';'" << endl;
                break;
            case Token::UnknownToken:
                cout << "Found Unknown Token" << endl;
                break;
            case Token::EndOfInputToken:
                cout << "Found End of Input" << endl;
                break;
            default:
                cout << "Should not get here" << endl;
            }
        } while (Toke.GetType () != Token::EndOfInputToken);
    Token::CloseFile ();
    }
