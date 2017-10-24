#include "Token.h"
#include <iostream>

Token::Token ()
	{
	}

Token::Token (TokenType T, NumberType V)
	{
	Type	= T;
	Value	= V;
	}

Token::~Token ()
	{
	//std::cout << "deleting token" << std::endl;
	}

Token & Token::operator =	(const Token & T)
	{
	Type			= T.Type;
	IsLeftSideDone	= T.IsLeftSideDone;
	Value			= T.Value;
	return *this;
	}
