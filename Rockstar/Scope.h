#pragma once
#include "IVariable.h"
#include <memory>
#include <map>

class Scope
{
public:
	Scope();
	const std::shared_ptr<IVariable> getVariable(const std::string& name);
	void setVariable(const std::string& name, const std::shared_ptr<IVariable> value);
	std::shared_ptr<IVariable> getLast() const;

private:
	std::string _lastVar;
	std::map<std::string, std::shared_ptr<IVariable>> _variables;
};

