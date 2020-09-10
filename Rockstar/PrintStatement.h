#pragma once
#include "ICodeBlock.h"
#include "IExpression.h"
#include <ostream>

class PrintStatement : public ICodeBlock
{
public:
	PrintStatement(std::shared_ptr<IExpression> exp);
	virtual void execute(Scope& scope);
private:
	std::shared_ptr<IExpression> _exp;
};

