#pragma once
#include "IExpression.h"
#include "GenericParser/include/Token.h"

class Constant : public IExpression
{
public:
	Constant(const Token& value);
	virtual IVariable* evaluate(Scope& scope) const;
private:
	Token _value;
};

