#include "Statement.h"
 
// STATIC VARIABLES FROM TOKEN CLASS //
 
WCS_String Statement::FileName;
 
Token::TokenType Statement::InputTable [] = {
                                            Token::EndOfInputToken,
                                            Token::UnknownToken,
                                            Token::VariableToken,
                                            Token::ConstantToken,
                                            Token::KeywordEvalToken,
                                            Token::KeywordExpToken,
                                            Token::KeywordValueToken,
                                            Token::OperatorPlusToken,
                                            Token::OperatorMinusToken,
                                            Token::OperatorAsteriskToken,
                                            Token::OperatorSlashToken,
                                            Token::SymbolOpenParenToken,
                                            Token::SymbolCloseParenToken,
                                            Token::SymbolSemiColonToken
                                            };
 
Statement::StatementFunc Statement::StateFunction [] = {
                                                        NotDone,                            // 0
                                                        GotBadStatement,                    // 1
                                                        GotEVAL,                            // 2
                                                        GotSemicolonAfterEVAL,              // 3
                                                        GotEXP,                             // 4
                                                        GotOperand,                         // 5
                                                        InsertBinaryPlusMinus,              // 6
                                                        InsertBinaryMultiplyDivide,         // 7
                                                        CloseParenAfterOperand,             // 8
                                                        GotNonSemicolon,                    // 9
                                                        SkippedToSemicolon,                 // 10
                                                        GotOpenParen,                       // 11
                                                        GotUnaryPlusMinus,                  // 12
                                                        GotSemicolonAfterExpression,        // 13
                                                        GotVALUE,                           // 14
                                                        GotVALUEVariable,                   // 15
                                                        GotVALUEVariableConstant,           // 16
                                                        GotVALUEVariableConstantSemicolon,  // 17
                                                        GotVALUEVariableMinus,              // 18
                                                        GotVALUEVariableMinusConstant,      // 19
                                                        GotEOF,                             // 20
                                                        GotUnknownToken                     // 21
                                                        };
 
 
Statement::UChar Statement::StateTable [Token::NumTokens] [NumStates] = {
    //                  Start   AFTER   START   AFTER   AFTER   SKIP2   AFTER   AFTER   AFTER   AFTER   
    //                          EVAL    EXP     OPERAND OPER    SEMI    VALUE   VALVAR  VVCONS  VVMINUS 
    /*  EVAL        */  {2,     1,      1,      1,      1,      9,      1,      1,      1,      1},
    /*  EXP         */  {4,     1,      1,      1,      1,      9,      1,      1,      1,      1},
    /*  VALUE       */  {14,    1,      1,      1,      1,      9,      1,      1,      1,      1},
    /*  CONSTANT    */  {1,     1,      5,      1,      5,      9,      1,      16,     1,      19},
    /*  VARIABLE    */  {1,     1,      5,      1,      5,      9,      15,     1,      1,      1},
    /*  (           */  {1,     1,      11,     11,     1,      9,      1,      1,      1,      1},
    /*  )           */  {1,     1,      1,      8,      1,      9,      1,      1,      1,      1},
    /*  +           */  {1,     1,      1,      6,      1,      9,      1,      1,      1,      1},
    /*  -           */  {1,     1,      12,     6,      12,     9,      1,      18,     1,      1},
    /*  *           */  {1,     1,      1,      7,      1,      9,      1,      1,      1,      1},
    /*  /           */  {1,     1,      1,      7,      1,      9,      1,      1,      1,      1},
    /*  ;           */  {1,     3,      13,     13,     1,      10,     1,      1,      17,     1},
    /*  EOF         */  {20,    20,     20,     20,     20,     20,     20,     20,     20,     20},
    /*  UNKNOWN     */  {21,    21,     21,     21,     21,     9,      21,     21,     21,     21}
    };
 
Statement & Statement::Build ()
    {
    StatementState CurrentState (StartGettingStatement);
    SetType (BadStatement);
    do  {
        Toke.Build ();
        int TType;
        TType = Toke.GetType ();
        CurrentState = StateFunction [StateTable [TType]  [CurrentState]] (*this, Toke);
        }while (CurrentState != StatementComplete);
    return *this;
    }
 
//Function 0)
Statement::StatementState Statement::NotDone (Statement & S, Token & T)
    {
    cout << "Program should not get here" << endl;
    S.MathTree.DeleteTree ();
    S.SetType(Statement::BadStatement);
    return StatementComplete;
    }
 
//Function 1)
Statement::StatementState Statement::GotBadStatement (Statement & S, Token & T)
    {
    S.SetType(Statement::BadStatement);
    cout << "Statement didn't make sense" << endl;
    S.MathTree.DeleteTree ();
    return SkipToSemicolon;
    }
 
//FUNCTION 2)   
Statement::StatementState Statement::GotEVAL (Statement & S, Token & T)
    {
    return Statement::AfterEVAL;
    }
 
//FUNCTION 3)   
Statement::StatementState Statement::GotSemicolonAfterEVAL (Statement & S, Token & T)
    {
    cout << "Answer: " << S.MathTree.Evaluate () << endl;
    return Statement::StatementComplete;
    }
 
 
//FUNCTION 4)   
Statement::StatementState Statement::GotEXP (Statement & S, Token & T)
    {
    S.MathTree.DeleteTree ();
    S.NumOpenParens = 0;
    return Statement::StartExpression;
    }
 
//FUNCTION 5)   
Statement::StatementState Statement::GotOperand (Statement & S, Token & T)
    {
    S.MathTree.InsertOperand (T);
    return Statement::AfterOperand;
    }
 
//FUNCTION 6)   
Statement::StatementState Statement::InsertBinaryPlusMinus (Statement & S, Token & T)
    {
    T.SetPrecedence ((Operator::Precedence) (Operator::BinaryPlusMinusPrecedence + (S.NumOpenParens * Operator::ParenthesesPrecedence)));
    S.MathTree.InsertBinaryOperator (T);
    return Statement::StartExpression;
    }
 
//FUNCTION 7)   
Statement::StatementState Statement::InsertBinaryMultiplyDivide (Statement & S, Token & T)
    {
    T.SetPrecedence ((Operator::Precedence) (Operator::MultiplyDividePrecedence + (S.NumOpenParens * Operator::ParenthesesPrecedence)));
    S.MathTree.InsertBinaryOperator (T);
    return Statement::StartExpression;
    }
 
//FUNCTION 8)   
Statement::StatementState Statement::CloseParenAfterOperand (Statement & S, Token & T)
    {
    if (S.NumOpenParens > 0)
            {
            S.NumOpenParens--;
            return Statement::AfterOperand;
            }
        else
            {
            cout << "BAD" << endl;
            S.MathTree.DeleteTree ();
            return Statement::SkipToSemicolon;
            }
    }
 
//FUNCTION 9)   
Statement::StatementState Statement::GotNonSemicolon (Statement & S, Token & T)
    {
    return Statement::SkipToSemicolon;
    }
 
//FUNCTION 10)  
Statement::StatementState Statement::SkippedToSemicolon (Statement & S, Token & T)
    {
    return Statement::StatementComplete;
    }
 
//FUNCTION 11)  
Statement::StatementState Statement::GotOpenParen (Statement & S, Token & T)
    {
    S.NumOpenParens++;
    return Statement::StartExpression;
    }
 
//FUNCTION 12)  
Statement::StatementState Statement::GotUnaryPlusMinus (Statement & S, Token & T)
    {
    T.SetPrecedence ((Operator::Precedence) ((int)Operator::UnaryPlusMinusPrecedence + (S.NumOpenParens * Operator::ParenthesesPrecedence)));
    S.MathTree.InsertUnaryOperator (T);
    return Statement::StartExpression;
    }
 
//FUNCTION 13)  
Statement::StatementState Statement::GotSemicolonAfterExpression (Statement & S, Token & T)
    {
    if (S.NumOpenParens == 0)
            {
            cout << "Statement Successfully entered" << endl;
            return Statement::StatementComplete;
            }
        else
            {
            cout << "Statement didn't make sense" << endl;
            cout << S.NumOpenParens << " Open Parens" << endl;
            S.MathTree.DeleteTree ();
            return StatementComplete;
            }
    }
 
//FUNCTION 14) 
Statement::StatementState Statement::GotVALUE (Statement & S, Token & T)
    {
    return Statement::AfterVALUE;
    }
     
//FUNCTION 15) 
Statement::StatementState Statement::GotVALUEVariable (Statement & S, Token & T)
    {
    S.SetWhich (T.GetWhich ());
    return Statement::AfterVALUEVariable;
    }
 
//FUNCTION 16) 
Statement::StatementState Statement::GotVALUEVariableConstant (Statement & S, Token & T)
    {
    S.MathTree.SetValue (S.GetWhich (), T.GetValue ());
    return AfterVALUEVariableConstant;
    }
 
//FUNCTION 17)
Statement::StatementState Statement::GotVALUEVariableConstantSemicolon (Statement & S, Token & T)
    {
    S.Type = Statement::ValueStatement;
    cout << "Set Variable " << S.Which << " to Value: " << S.Toke.GetValue () << endl;
    return Statement::StatementComplete;
    }
 
//FUNCTION 18) 
Statement::StatementState Statement::GotVALUEVariableMinus (Statement & S, Token & T)
    {
    return Statement::AfterVALUEVariableMinus;
    }
 
//FUNCTION 19) 
Statement::StatementState Statement::GotVALUEVariableMinusConstant (Statement & S, Token & T)
    {
    S.MathTree.SetValue (S.GetWhich (), -(T.GetValue ()));
    return Statement::AfterVALUEVariableConstant;
    }
 
//Function 20)
Statement::StatementState Statement::GotEOF (Statement & S, Token & T)
    {
    S.SetType(Statement::EndOfInput);
    S.MathTree.DeleteTree ();
    cout << "End of File" << endl;
    return StatementComplete;
    }
 
//Function 21
Statement::StatementState Statement::GotUnknownToken (Statement & S, Token & T)
    {
    cout << "Got a bad Token, skipping to semicolon" << endl;
    return SkipToSemicolon;
    }
 
void Statement::OpenFile (const WCS_String & S)
    {
    FileName.Copy(S);
    Toke.OpenFile(FileName);
    }
 
void Statement::CloseFile ()
    {
    Toke.CloseFile();
    }
