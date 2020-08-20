#pragma once
#include "IExpression.h"
class Pronoun : public IExpression
{
public:
	virtual std::shared_ptr<IVariable> evaluate(Scope& scope) const;
};

