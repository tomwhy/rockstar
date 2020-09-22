#pragma once
#include "IModifyStatement.h"

class JoinStatement : public IModifyStatement
{
public:
	JoinStatement(std::shared_ptr<IExpression> exp, std::shared_ptr<VariableName> dest = {}, std::shared_ptr<IExpression> argument = {});
	JoinStatement(const CompiledObject& obj);
protected:
	virtual std::shared_ptr<IVariable> modify(Scope& scope);

	virtual CompiledObject serialize() const;

private:
	CompiledObject checkObjectCode(const CompiledObject& obj);
};
