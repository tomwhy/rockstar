#pragma once
#include "IExpression.h"
#include "GenericParser/include/Token.h"

class Utils
{
public:
	static const IExpression* createExpression(const Token& token);
};

