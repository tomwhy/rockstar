#pragma once
#include "IExpression.h"
class Pronoun : public IExpression
{
public:
	Pronoun(std::shared_ptr<IExpression> index = {});
	virtual std::shared_ptr<IVariable> evaluate(Scope& scope) const;
private:
	std::shared_ptr<IExpression> _index;
};

