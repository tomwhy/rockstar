#pragma once
#include "Constant.h"
class PoeticExpression : public Constant
{
public:
	PoeticExpression(const Token& token, bool stringLiteral);

private:
	static Token parseLiteral(const Token& token, bool stringLiteral);
};

