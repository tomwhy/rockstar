#pragma once
#include "IExpression.h"

class LogicNotExpression : public IExpression
{
public:
	LogicNotExpression(std::shared_ptr<IExpression> exp);
	LogicNotExpression(const CompiledObject& obj);
	virtual std::shared_ptr<IVariable> evaluate(Scope& scope) const;
	virtual CompiledObject serialize() const;

private:
	std::shared_ptr<IExpression> _exp;
};

