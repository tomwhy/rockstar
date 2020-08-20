#pragma once
#include "IExpression.h"
#include "GenericParser/include/Token.h"

class Utils
{
public:
	static std::shared_ptr<IExpression> createExpression(const Token& token);
	static std::string lower(const std::string& str);
};

