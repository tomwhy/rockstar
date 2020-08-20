#pragma once
#include "IVariable.h"
#include "Scope.h"

class IExpression
{
public:
	virtual IVariable* evaluate(Scope& scope) const = 0;
};