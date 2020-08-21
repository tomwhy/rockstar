#pragma once
#include "ICodeBlock.h"
#include "IExpression.h"
#include "VariableName.h"
#include  <memory>

class IModifyStatement : public ICodeBlock
{
public:
	IModifyStatement(std::shared_ptr<IExpression> exp, std::shared_ptr<VariableName> dest = {}, std::shared_ptr<IExpression> argument = {});
	virtual void execute(Scope& scope);
protected:
	virtual std::shared_ptr<IVariable> modify() = 0;

	std::shared_ptr<IExpression> _exp;
	std::shared_ptr<IExpression> _argument;

private:
	std::shared_ptr<VariableName> _dest;
};

