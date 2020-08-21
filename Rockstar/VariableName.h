#pragma once
#include "IExpression.h"
class VariableName : public IExpression
{
public:
	VariableName(const std::string& name);
	VariableName(const std::string& name, std::shared_ptr<IExpression> index);
	virtual std::shared_ptr<IVariable> evaluate(Scope& scope) const;
private:
	std::string _name;
	std::shared_ptr<IExpression> _index;
};

