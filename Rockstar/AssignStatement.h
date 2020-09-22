#pragma once
#include "ICodeBlock.h"
#include "IExpression.h"
#include "VariableName.h"


class AssignStatement : public ICodeBlock
{
public:
	AssignStatement(std::shared_ptr<VariableName> name, std::shared_ptr<IExpression> value);
	AssignStatement(const AssignStatement& other);
	AssignStatement(const CompiledObject& obj);
	
	virtual void execute(Scope& scope);
	virtual CompiledObject serialize() const;
private:
	std::shared_ptr<VariableName> _var;
	std::shared_ptr<IExpression> _exp;
};

