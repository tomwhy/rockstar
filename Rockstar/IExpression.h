#pragma once
#include "IVariable.h"
#include "Scope.h"
#include "CompiledObject.h"

class IExpression
{
public:
	virtual ~IExpression() {};
	virtual std::shared_ptr<IVariable> evaluate(Scope& scope) const = 0;
	virtual CompiledObject serialize() const = 0;  // code (byte), length (sizeof unsigned int), data
	virtual bool isVariable() const { return false; }
};