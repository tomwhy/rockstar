#pragma once
#include "IExpression.h"
#include "VariableName.h"

class Pronoun : public VariableName
{
public:
	Pronoun(std::shared_ptr<IExpression> index = {});
	virtual std::shared_ptr<IVariable> evaluate(Scope& scope) const;

	virtual std::string name(Scope& scope) const;
private:
	std::shared_ptr<IExpression> _index;
};

