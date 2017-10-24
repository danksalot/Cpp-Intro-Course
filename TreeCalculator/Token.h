#ifndef TOKEN_H
#define TOKEN_H

class Token
	{
	public:
		typedef	long			NumberType;
		typedef unsigned long	ULONG;
		enum	TokenType	{
							OperatorPlus,
							OperatorMinus,
							OperatorMultiply,
							OperatorDivide,
							Constant,
							Variable
							};
		enum PrecedenceType	{
							AddSubtractPrecedence,
							MultDividePrecedence,
							UnaryPlusMinusPrecedence
							};
				Token	();
				Token	(const Token &);
				Token	(TokenType, NumberType);
				~Token	();
		Token &	operator =	(const Token &);

		bool				IsLeftSideDone;
		TokenType			Type;
		union
			{
			NumberType		Value;
			ULONG			Precedence;		//CHANGED FROM PrecidenceType DATA TYPE
			ULONG			Which;
			};
	};

#endif
