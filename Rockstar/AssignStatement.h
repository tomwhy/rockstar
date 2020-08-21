#pragma once
#include "ICodeBlock.h"
#include "IExpression.h"
#include "VariableName.h"

class AssignStatement : public ICodeBlock
{
public:
	AssignStatement(std::shared_ptr<VariableName> name, std::shared_ptr<IExpression> value);
	AssignStatement(const AssignStatement& other);
	
	virtual void execute(Scope& scope);
private:
	std::shared_ptr<VariableName> _var;
	std::shared_ptr<IExpression> _exp;
};

