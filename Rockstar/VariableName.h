#pragma once
#include "IExpression.h"
class VariableName : public IExpression
{
public:
	VariableName(const std::string& name);
	virtual const IVariable* evaluate(Scope& scope) const;
private:
	std::string _name;
};

