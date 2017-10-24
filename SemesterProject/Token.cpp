#define TOKEN_CPP
 
#include "Token.h"
 
//**********  Static Variables from Token Class **********
 
Token::UChar Token::LastChar;
 
ifstream Token::SourceFile;
 
Token::InputType Token::InputTable [] =         {
                                                InputUnknown,       // 00
                                                InputUnknown,       // 01
                                                InputUnknown,       // 02
                                                InputUnknown,       // 03
                                                InputUnknown,       // 04
                                                InputUnknown,       // 05
                                                InputUnknown,       // 06
                                                InputUnknown,       // 07
                                                InputUnknown,       // 08
                                                InputUnknown,       // 09
                                                InputSpace,         // 0A
                                                InputUnknown,       // 0B
                                                InputUnknown,       // 0C
                                                InputSpace,         // 0D
                                                InputUnknown,       // 0E
                                                InputUnknown,       // 0F
                                                InputUnknown,       // 10
                                                InputUnknown,       // 11
                                                InputUnknown,       // 12
                                                InputUnknown,       // 13
                                                InputSpace,         // 14
                                                InputUnknown,       // 15
                                                InputUnknown,       // 16
                                                InputUnknown,       // 17
                                                InputUnknown,       // 18
                                                InputUnknown,       // 19
                                                InputUnknown,       // 1A
                                                InputUnknown,       // 1B
                                                InputUnknown,       // 1C
                                                InputUnknown,       // 1D
                                                InputUnknown,       // 1E
                                                InputUnknown,       // 1F
                                                InputSpace,         // 20
                                                InputUnknown,       // 21
                                                InputUnknown,       // 22
                                                InputUnknown,       // 23
                                                InputUnknown,       // 24
                                                InputUnknown,       // 25
                                                InputUnknown,       // 26
                                                InputUnknown,       // 27
                                                InputOpenParen,     // 28
                                                InputCloseParen,    // 29
                                                InputAsterisk,      // 2A
                                                InputPlus,          // 2B
                                                InputUnknown,       // 2C
                                                InputMinus,         // 2D
                                                InputUnknown,       // 2E
                                                InputSlash,         // 2F
                                                Input0,             // 30
                                                Input1,             // 31
                                                Input2,             // 32
                                                Input3,             // 33
                                                Input4,             // 34
                                                Input5,             // 35
                                                Input6,             // 36
                                                Input7,             // 37
                                                Input8,             // 38
                                                Input9,             // 39
                                                InputUnknown,       // 3A
                                                InputSemiColon,     // 3B
                                                InputUnknown,       // 3C
                                                InputUnknown,       // 3D
                                                InputUnknown,       // 3E
                                                InputUnknown,       // 3F
                                                InputUnknown,       // 40
                                                InputA,             // 41
                                                InputUnknown,       // 42
                                                InputUnknown,       // 43
                                                InputUnknown,       // 44
                                                InputE,             // 45
                                                InputUnknown,       // 46
                                                InputUnknown,       // 47
                                                InputUnknown,       // 48
                                                InputUnknown,       // 49
                                                InputUnknown,       // 4A
                                                InputUnknown,       // 4B
                                                InputL,             // 4C
                                                InputUnknown,       // 4D
                                                InputUnknown,       // 4E
                                                InputUnknown,       // 4F
                                                InputP,             // 50
                                                InputUnknown,       // 51
                                                InputUnknown,       // 52
                                                InputUnknown,       // 53
                                                InputUnknown,       // 54
                                                InputU,             // 55
                                                InputV,             // 56
                                                InputUnknown,       // 57
                                                InputX,             // 58
                                                InputUnknown,       // 59
                                                InputUnknown,       // 5A
                                                InputUnknown,       // 5B
                                                InputUnknown,       // 5C
                                                InputUnknown,       // 5D
                                                InputUnknown,       // 5E
                                                InputUnknown,       // 5F
                                                InputUnknown,       // 60
                                                InputA,             // 61
                                                InputUnknown,       // 62
                                                InputUnknown,       // 63
                                                InputUnknown,       // 64
                                                InputE,             // 65
                                                InputUnknown,       // 66
                                                InputUnknown,       // 67
                                                InputUnknown,       // 68
                                                InputUnknown,       // 69
                                                InputUnknown,       // 6A
                                                InputUnknown,       // 6B
                                                InputL,             // 6C
                                                InputUnknown,       // 6D
                                                InputUnknown,       // 6E
                                                InputUnknown,       // 6F
                                                InputP,             // 70
                                                InputUnknown,       // 71
                                                InputUnknown,       // 72
                                                InputUnknown,       // 73
                                                InputUnknown,       // 74
                                                InputU,             // 75
                                                InputV,             // 76
                                                InputUnknown,       // 77
                                                InputX,             // 78
                                                InputUnknown,       // 79
                                                InputUnknown,       // 7A
                                                InputUnknown,       // 7B
                                                InputUnknown,       // 7C
                                                InputUnknown,       // 7D
                                                InputUnknown,       // 7E
                                                InputUnknown,       // 7F
                                                InputUnknown,       // 80
                                                InputUnknown,       // 81
                                                InputUnknown,       // 82
                                                InputUnknown,       // 83
                                                InputUnknown,       // 84
                                                InputUnknown,       // 85
                                                InputUnknown,       // 86
                                                InputUnknown,       // 87
                                                InputUnknown,       // 88
                                                InputUnknown,       // 89
                                                InputUnknown,       // 8A
                                                InputUnknown,       // 8B
                                                InputUnknown,       // 8C
                                                InputUnknown,       // 8D
                                                InputUnknown,       // 8E
                                                InputUnknown,       // 8F
                                                InputUnknown,       // 90
                                                InputUnknown,       // 91
                                                InputUnknown,       // 92
                                                InputUnknown,       // 93
                                                InputUnknown,       // 94
                                                InputUnknown,       // 95
                                                InputUnknown,       // 96
                                                InputUnknown,       // 97
                                                InputUnknown,       // 98
                                                InputUnknown,       // 99
                                                InputUnknown,       // 9A
                                                InputUnknown,       // 9B
                                                InputUnknown,       // 9C
                                                InputUnknown,       // 9D
                                                InputUnknown,       // 9E
                                                InputUnknown,       // 9F
                                                InputUnknown,       // A0
                                                InputUnknown,       // A1
                                                InputUnknown,       // A2
                                                InputUnknown,       // A3
                                                InputUnknown,       // A4
                                                InputUnknown,       // A5
                                                InputUnknown,       // A6
                                                InputUnknown,       // A7
                                                InputUnknown,       // A8
                                                InputUnknown,       // A9
                                                InputUnknown,       // AA
                                                InputUnknown,       // AB
                                                InputUnknown,       // AC
                                                InputUnknown,       // AD
                                                InputUnknown,       // AE
                                                InputUnknown,       // AF
                                                InputUnknown,       // B0
                                                InputUnknown,       // B1
                                                InputUnknown,       // B2
                                                InputUnknown,       // B3
                                                InputUnknown,       // B4
                                                InputUnknown,       // B5
                                                InputUnknown,       // B6
                                                InputUnknown,       // B7
                                                InputUnknown,       // B8
                                                InputUnknown,       // B9
                                                InputUnknown,       // BA
                                                InputUnknown,       // BB
                                                InputUnknown,       // BC
                                                InputUnknown,       // BD
                                                InputUnknown,       // BE
                                                InputUnknown,       // BF
                                                InputUnknown,       // C0
                                                InputUnknown,       // C1
                                                InputUnknown,       // C2
                                                InputUnknown,       // C3
                                                InputUnknown,       // C4
                                                InputUnknown,       // C5
                                                InputUnknown,       // C6
                                                InputUnknown,       // C7
                                                InputUnknown,       // C8
                                                InputUnknown,       // C9
                                                InputUnknown,       // CA
                                                InputUnknown,       // CB
                                                InputUnknown,       // CC
                                                InputUnknown,       // CD
                                                InputUnknown,       // CE
                                                InputUnknown,       // CF
                                                InputUnknown,       // D0
                                                InputUnknown,       // D1
                                                InputUnknown,       // D2
                                                InputUnknown,       // D3
                                                InputUnknown,       // D4
                                                InputUnknown,       // D5
                                                InputUnknown,       // D6
                                                InputUnknown,       // D7
                                                InputUnknown,       // D8
                                                InputUnknown,       // D9
                                                InputUnknown,       // DA
                                                InputUnknown,       // DB
                                                InputUnknown,       // DC
                                                InputUnknown,       // DD
                                                InputUnknown,       // DE
                                                InputUnknown,       // DF
                                                InputUnknown,       // E0
                                                InputUnknown,       // E1
                                                InputUnknown,       // E2
                                                InputUnknown,       // E3
                                                InputUnknown,       // E4
                                                InputUnknown,       // E5
                                                InputUnknown,       // E6
                                                InputUnknown,       // E7
                                                InputUnknown,       // E8
                                                InputUnknown,       // E9
                                                InputUnknown,       // EA
                                                InputUnknown,       // EB
                                                InputUnknown,       // EC
                                                InputUnknown,       // ED
                                                InputUnknown,       // EE
                                                InputUnknown,       // EF
                                                InputUnknown,       // F0
                                                InputUnknown,       // F1
                                                InputUnknown,       // F2
                                                InputUnknown,       // F3
                                                InputUnknown,       // F4
                                                InputUnknown,       // F5
                                                InputUnknown,       // F6
                                                InputUnknown,       // F7
                                                InputUnknown,       // F8
                                                InputUnknown,       // F9
                                                InputUnknown,       // FA
                                                InputUnknown,       // FB
                                                InputUnknown,       // FC
                                                InputUnknown,       // FD
                                                InputUnknown,       // FE
                                                EndOfFile           // FF
                                                };
 
Token::TokenFunc Token::StateFunction [] =      {
                                                NotYetDone,         //  0
                                                BadToken,           //  1
                                                GotE,               //  2
                                                GotEV,              //  3
                                                GotEVA,             //  4
                                                GotEVAL,            //  5
                                                GotV,               //  6
                                                GotVA,              //  7
                                                GotVAL,             //  8
                                                GotVALU,            //  9
                                                GotVALUE,           //  10
                                                GotEX,              //  11
                                                GotEXP,             //  12
                                                GotVDigit,          //  13
                                                GotVDigitDigit,     //  14
                                                GotDigit,           //  15
                                                GotAnotherDigit,    //  16
                                                GotNonDigit,        //  17
                                                GotPlus,            //  18
                                                GotMinus,           //  19
                                                GotAsterisk,        //  20
                                                GotSlash,           //  21
                                                GotOpenParen,       //  22
                                                GotCloseParen,      //  23
                                                GotSemicolon,       //  24
                                                GotSpace,           //  25
                                                GotEOF,             //  26
                                                FinishedBadToken    //  27
                                                };
 
Token::UChar Token::StateTable [NumInputs] [NumStates] =    {
                        //                  //  START   E       EV      EVA     V       VA      VAL     VALU    EX      VDIG    DIG     UNEXP   
                        /*  InputUnknown    */  {1,     1,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1},
                        /*  InputA          */  {1,     1,      4,      1,      7,      1,      1,      1,      1,      1,      1,      1},
                        /*  InputE          */  {2,     1,      1,      1,      1,      1,      1,      10,     1,      1,      1,      1},
                        /*  InputL          */  {1,     1,      1,      5,      1,      8,      1,      1,      1,      1,      1,      1},
                        /*  InputP          */  {1,     1,      1,      1,      1,      1,      1,      1,      12,     1,      1,      1},
                        /*  InputU          */  {1,     1,      1,      1,      1,      1,      9,      1,      1,      1,      1,      1},
                        /*  InputV          */  {6,     3,      1,      1,      1,      1,      1,      1,      1,      1,      1,      1},
                        /*  InputX          */  {1,     11,     1,      1,      1,      1,      1,      1,      1,      1,      1,      1},
                        /*  Input0          */  {15,    1,      1,      1,      13,     1,      1,      1,      1,      14,     16,     1},
                        /*  Input1          */  {15,    1,      1,      1,      13,     1,      1,      1,      1,      14,     16,     1},
                        /*  Input2          */  {15,    1,      1,      1,      13,     1,      1,      1,      1,      14,     16,     1},
                        /*  Input3          */  {15,    1,      1,      1,      13,     1,      1,      1,      1,      14,     16,     1},
                        /*  Input4          */  {15,    1,      1,      1,      13,     1,      1,      1,      1,      14,     16,     1},
                        /*  Input5          */  {15,    1,      1,      1,      13,     1,      1,      1,      1,      14,     16,     1},
                        /*  Input6          */  {15,    1,      1,      1,      13,     1,      1,      1,      1,      14,     16,     1},
                        /*  Input7          */  {15,    1,      1,      1,      13,     1,      1,      1,      1,      14,     16,     1},
                        /*  Input8          */  {15,    1,      1,      1,      13,     1,      1,      1,      1,      14,     16,     1},
                        /*  Input9          */  {15,    1,      1,      1,      13,     1,      1,      1,      1,      14,     16,     1},
                        /*  InputPlus       */  {18,    1,      1,      1,      1,      1,      1,      1,      1,      1,      17,     1},
                        /*  InputMinus      */  {19,    1,      1,      1,      1,      1,      1,      1,      1,      1,      17,     1},
                        /*  InputAsterisk   */  {20,    1,      1,      1,      1,      1,      1,      1,      1,      1,      17,     1},
                        /*  InputSlash      */  {21,    1,      1,      1,      1,      1,      1,      1,      1,      1,      17,     1},
                        /*  InputOpenParen  */  {22,    1,      1,      1,      1,      1,      1,      1,      1,      1,      17,     1},
                        /*  InputCloseParen */  {23,    1,      1,      1,      1,      1,      1,      1,      1,      1,      17,     1},
                        /*  InputSemiColon  */  {24,    1,      1,      1,      1,      1,      1,      1,      1,      1,      17,     1},         
                        /*  InputSpace      */  {25,    1,      1,      1,      1,      1,      1,      1,      1,      1,      17,     27},
                        /*  EndOfFile       */  {26,    26,     26,     26,     26,     26,     26,     26,     26,     26,     26,     26},
                                                };
 
Variable Token::VariableArray [NumVariables];
 
//********** Methods from Token Class **********
 
Token & Token::Build ()
    {
    if (SourceFile.is_open ())
            {
            TokenState CurrentState (StartGettingToken);
            SetType (UnknownToken);
            do  {
                CurrentState = StateFunction [StateTable [GetInputChar ()] [CurrentState] ] (*this);
                } while (CurrentState != TokenComplete);
            return *this;
            }
        else
            throw TokenFileNotOpen;
    }
 
Token::TokenState Token::NotYetDone (Token &)
    {
    cout << "Still needs to be coded" << endl;
    return TokenComplete;
    }
 
Token::TokenState Token::BadToken (Token & T)
    {
    T.SetType (UnknownToken);
    return AfterUnexpected;
    }
 
Token::TokenState Token::GotE (Token &)
    {
    return AfterE;
    }
 
Token::TokenState Token::GotEV (Token &)
    {
    return AfterEV;
    }
 
Token::TokenState Token::GotEVA (Token &)
    {
    return AfterEVA;
    }
 
Token::TokenState Token::GotEVAL (Token & T)
    {
    T.SetType (KeywordEvalToken);
    return TokenComplete;
    }
 
Token::TokenState Token::GotV (Token &)
    {
    return AfterV;
    }
 
Token::TokenState Token::GotVA (Token &)
    {
    return AfterVA;
    }
 
Token::TokenState Token::GotVAL (Token &)
    {
    return AfterVAL;
    }
 
Token::TokenState Token::GotVALU (Token &)
    {
    return AfterVALU;
    }
 
Token::TokenState Token::GotVALUE (Token & T)
    {
    T.SetType (KeywordValueToken);
    return TokenComplete;
    }
 
Token::TokenState Token::GotEX (Token &)
    {
    return AfterEX;
    }
 
Token::TokenState Token::GotEXP (Token & T)
    {
    T.SetType (KeywordExpToken);
    return TokenComplete;
    }
 
Token::TokenState Token::GotVDigit (Token & T)
    {
    T.SetWhich ((LastChar - '0') * 10);
    return AfterVDigit;
    }
 
Token::TokenState Token::GotVDigitDigit (Token & T)
    {
    T.SetType (VariableToken);
    T.SetWhich (T.GetWhich () + (LastChar - '0'));
    T.SetValue (0);
    cout << T.GetValue () << endl;
    return TokenComplete;
    }
 
Token::TokenState Token::GotDigit (Token & T)
    {
    T.SetType (ConstantToken);
    T.SetValue (LastChar - '0');
    return AfterDigit;
    }
 
Token::TokenState Token::GotAnotherDigit (Token & T)
    {
    T.SetValue ((T.GetValue () * 10) + (LastChar - '0'));
    return AfterDigit;
    }
 
Token::TokenState Token::GotNonDigit (Token & T)
    {
    T.PutBackLastChar ();
    return TokenComplete;
    }
 
Token::TokenState Token::GotPlus (Token & T)
    {
    T.SetType (OperatorPlusToken);
    T.SetPrecedence (Operator::BinaryPlusMinusPrecedence);
    return TokenComplete;
    }
 
Token::TokenState Token::GotMinus (Token & T)
    {
    T.SetType (OperatorMinusToken);
    T.SetPrecedence (Operator::BinaryPlusMinusPrecedence);
    return TokenComplete;
    }
 
Token::TokenState Token::GotAsterisk (Token & T)
    {
    T.SetType (OperatorAsteriskToken);
    T.SetPrecedence (Operator::MultiplyDividePrecedence);
    return TokenComplete;
    }
 
Token::TokenState Token::GotSlash (Token & T)
    {
    T.SetType (OperatorSlashToken);
    T.SetPrecedence (Operator::MultiplyDividePrecedence);
    return TokenComplete;
    }
 
Token::TokenState Token::GotOpenParen (Token & T)
    {
    T.SetType (SymbolOpenParenToken);
    return TokenComplete;
    }
 
Token::TokenState Token::GotCloseParen (Token & T)
    {
    T.SetType (SymbolCloseParenToken);
    return TokenComplete;
    }
 
Token::TokenState Token::GotSemicolon (Token & T)
    {
    T.SetType (SymbolSemiColonToken);
    return TokenComplete;
    }
 
Token::TokenState Token::GotSpace (Token &)
    {
    return StartGettingToken;
    }
 
Token::TokenState Token::GotEOF (Token & T)
    {
    T.SetType (EndOfInputToken);
    return TokenComplete;
    }
 
Token::TokenState Token::FinishedBadToken (Token & T)
    {
    T.SetType (UnknownToken);
    return TokenComplete;
    }
