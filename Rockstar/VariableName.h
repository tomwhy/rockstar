#pragma once
#include "IExpression.h"

class VariableName : public IExpression
{
public:
	VariableName(const std::string& name);
	VariableName(const std::string& name, std::shared_ptr<IExpression> index);
	VariableName(const VariableName& other);

	virtual std::shared_ptr<IVariable> evaluate(Scope& scope) const;
	virtual bool isVariable() const;

	virtual std::string name(Scope& scope) const;
	std::string index(Scope& scope) const;
	bool hasIndex() const;
	
private:
	std::string _name;
	std::shared_ptr<IExpression> _index;
};

