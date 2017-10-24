#ifndef STATEMENT_H
#define STATEMENT_H
 
#include <fstream>
#include <WCS_String.h>
#include <WCS_Pointer.h>
 
#include "Token.h"
#include "MathTree.h"
 
using namespace std;
 
class Statement: public RefCount
    {
    public:
        typedef unsigned char   UChar;
 
        enum    Exception       {
                                TokenFileNotOpen
                                };
 
        enum    StatementType   {
                                BadStatement,
                                EvalStatement,
                                ValueStatement,
                                ExpressionStatement,
                                EndOfInput,
 
                                NumStatements
                                };
 
                        Statement   ();
        explicit        Statement   (const Statement &);
                        ~Statement  ();
 
        Statement &     Build       ();
        void            OpenFile    (const WCS_String &);
        void            CloseFile   ();
        StatementType   GetType     () const;
        int             GetWhich    () const;
 
    private:
 
        enum    StatementState {
                                StatementComplete = -1,
                                StartGettingStatement,
                                AfterEVAL,
                                StartExpression,
                                AfterOperand,
                                AfterOperator,
                                SkipToSemicolon,
                                AfterVALUE,
                                AfterVALUEVariable,
                                AfterVALUEVariableConstant,
                                AfterVALUEVariableMinus,
 
                                NumStates
                                };
 
        typedef int             State;
        typedef StatementState  (*StatementFunc)    (Statement &, Token &);
 
        //  *************   DATA    ******************//
        StatementType       Type;
        MathTree            MathTree;
        Token               Toke;
        int                 NumOpenParens;
        union
            {
            int                 Which;
            int                 Precedence;
            Variable::ValueType Value;
            };
 
        //  *************   Statement State Functions   *****************
 
        static  Token::TokenType        InputTable [];
        static  WCS_String              FileName;
        static  StatementFunc           StateFunction [];
        static  UChar                   StateTable [Token::NumTokens] [NumStates];
        void    SetWhich                (int);
        void    SetType                 (StatementType);
 
        static  StatementState          NotDone                                 (Statement &, Token &);
        static  StatementState          GotBadStatement                         (Statement &, Token &);
        static  StatementState          GotEVAL                                 (Statement &, Token &);
        static  StatementState          GotSemicolonAfterEVAL                   (Statement &, Token &);
        static  StatementState          GotEXP                                  (Statement &, Token &);
        static  StatementState          GotOperand                              (Statement &, Token &);
        static  StatementState          InsertBinaryPlusMinus                   (Statement &, Token &);
        static  StatementState          InsertBinaryMultiplyDivide              (Statement &, Token &);
        static  StatementState          CloseParenAfterOperand                  (Statement &, Token &);
        static  StatementState          GotNonSemicolon                         (Statement &, Token &);
        static  StatementState          SkippedToSemicolon                      (Statement &, Token &);
        static  StatementState          GotOpenParen                            (Statement &, Token &);
        static  StatementState          GotUnaryPlusMinus                       (Statement &, Token &);
        static  StatementState          GotSemicolonAfterExpression             (Statement &, Token &);
        static  StatementState          GotVALUE                                (Statement &, Token &);
        static  StatementState          GotVALUEVariable                        (Statement &, Token &);
        static  StatementState          GotVALUEVariableConstant                (Statement &, Token &);
        static  StatementState          GotVALUEVariableConstantSemicolon       (Statement &, Token &);
        static  StatementState          GotVALUEVariableMinus                   (Statement &, Token &);
        static  StatementState          GotVALUEVariableMinusConstant           (Statement &, Token &);
        static  StatementState          GotSpace                                (Statement &, Token &);
        static  StatementState          GotEOF                                  (Statement &, Token &);
        static  StatementState          GotUnknownToken                         (Statement &, Token &);
 
    };
 
inline Statement::StatementType Statement::GetType () const
    {
    return Type;
    }
 
inline void Statement::SetType (StatementType T)
    {
    Type = T;
    }
 
inline int Statement::GetWhich () const
    {
    return Which;
    }
 
inline void Statement::SetWhich (int W)
    {
    Which = W;
    }
 
inline Statement::Statement ()
    {
    }
 
inline Statement::Statement (const Statement & S)
    {
    }
 
inline Statement::~Statement ()
    {
    }
 
#endif
