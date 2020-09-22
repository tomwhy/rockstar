#pragma once
#include "ICodeBlock.h"
#include "IExpression.h"
#include <ostream>

class PrintStatement : public ICodeBlock
{
public:
	PrintStatement(std::shared_ptr<IExpression> exp);
	PrintStatement(const CompiledObject& obj);
	virtual void execute(Scope& scope);
	virtual CompiledObject serialize() const;
private:
	std::shared_ptr<IExpression> _exp;
};

