#pragma once
#include "ICodeBlock.h"
#include "IExpression.h"
#include "VariableName.h"

class AssignStatement : public ICodeBlock
{
public:
	AssignStatement(const std::string& name, std::shared_ptr<IExpression> value);
	AssignStatement(const std::string& name, std::shared_ptr<IExpression> index, std::shared_ptr<IExpression> value);
	
	virtual void execute(Scope& scope);
private:
	std::string _name;
	std::shared_ptr<IExpression> _index;
	std::shared_ptr<IExpression> _exp;
};

