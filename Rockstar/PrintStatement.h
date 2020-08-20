#pragma once
#include "ICodeBlock.h"
#include "IExpression.h"

class PrintStatement : public ICodeBlock
{
public:
	PrintStatement(std::shared_ptr<IExpression> exp);
	~PrintStatement();
	virtual void execute(Scope& scope);
private:
	std::shared_ptr<IExpression> _exp;
};

