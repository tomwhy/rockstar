#pragma once
#include "IModifyStatement.h"
class CastStatement : public IModifyStatement
{
public:
	CastStatement(std::shared_ptr<IExpression> exp, std::shared_ptr<VariableName> dest = {}, std::shared_ptr<IExpression> argument = {});
	CastStatement(const CompiledObject& obj);
	virtual CompiledObject serialize() const;
protected:
	virtual std::shared_ptr<IVariable> modify(Scope& scope);
private:
	CompiledObject checkObjectCode(const CompiledObject& obj);
};

