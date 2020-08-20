#pragma once
#include "IVariable.h"
#include "Scope.h"

class IExpression
{
public:
	virtual ~IExpression() {};
	virtual std::shared_ptr<IVariable> evaluate(Scope& scope) const = 0;
};