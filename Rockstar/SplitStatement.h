#pragma once
#include "IModifyStatement.h"

class SplitStatement : public IModifyStatement
{
public:
	SplitStatement(std::shared_ptr<IExpression> exp, std::shared_ptr<VariableName> dest = {}, std::shared_ptr<IExpression> argument = {});
	SplitStatement(const CompiledObject& obj);
	virtual CompiledObject serialize() const;
protected:
	virtual std::shared_ptr<IVariable> modify(Scope& scope);

private:
	CompiledObject checkObjectCode(const CompiledObject& obj);
};

