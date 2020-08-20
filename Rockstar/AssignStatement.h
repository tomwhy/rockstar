#pragma once
#include "ICodeBlock.h"
#include "IExpression.h"

class AssignStatement : public ICodeBlock
{
public:
	AssignStatement(const std::string& name, const IExpression* value);
	~AssignStatement();
	
	virtual void execute(Scope& scope);
private:
	std::string _name;
	const IExpression* _exp;
};

