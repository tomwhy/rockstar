#pragma once
#include "IVariable.h"
#include <memory>
#include <map>

class IExpression;
class VariableName;

class Scope
{
public:
	Scope();
	const std::shared_ptr<IVariable> getVariable(std::shared_ptr<VariableName> var);
	void setVariable(std::shared_ptr<VariableName> var, const std::shared_ptr<IVariable> value);
	std::shared_ptr<IVariable> getLast() const;
	std::string getLastName() const;

private:
	std::string _lastVar;
	std::map<std::string, std::shared_ptr<IVariable>> _variables;
};

