#pragma once
#include "IVariable.h"
#include <map>

class Scope
{
public:
	Scope();
	~Scope();
	const IVariable* getVariable(const std::string& name) const;
	void setVariable(const std::string& name, IVariable* value);

private:
	std::map<std::string, const IVariable*> _variables;
};

