#include "TreeToken.h"
#include <iostream>
 
TreeToken::TreeToken ()
    {
    }
 
TreeToken::TreeToken (TokenType T, NumberType V)
    {
    Type    = T;
    Value   = V;
    }
 
TreeToken::~TreeToken ()
    {
    }
 
TreeToken & TreeToken::operator =   (const TreeToken & T)
    {
    Type            = T.Type;
    IsLeftSideDone  = T.IsLeftSideDone;
    Value           = T.Value;
    return *this;
    }
