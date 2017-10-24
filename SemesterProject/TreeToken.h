#ifndef TREE_TOKEN_H
#define TREE_TOKEN_H
 
class TreeToken
    {
    public:
        typedef long            NumberType;
        typedef unsigned long   ULONG;
        enum    TokenType   {
                            OperatorPlus,
                            OperatorMinus,
                            OperatorMultiply,
                            OperatorDivide,
                            Constant,
                            Variable
                            };
        enum PrecedenceType {
                            AddSubtractPrecedence,
                            MultDividePrecedence,
                            UnaryPlusMinusPrecedence
                            };
                TreeToken   ();
                TreeToken   (const TreeToken &);
                TreeToken   (TokenType, NumberType);
                ~TreeToken  ();
        TreeToken & operator =  (const TreeToken &);
 
        bool                IsLeftSideDone;
        TokenType           Type;
        union
            {
            NumberType      Value;
            ULONG           Precedence;
            ULONG           Which;
            };
    };
 
#endif
