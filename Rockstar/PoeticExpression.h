#pragma once
#include "Constant.h"
class PoeticExpression : public Constant
{
public:
	PoeticExpression(const std::string& value, bool stringLiteral);

private:
	static Token parseLiteral(const std::string& value, bool stringLiteral);
};
