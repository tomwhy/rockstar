#include "Scope.h"
#include "InterpeterException.h"

Scope::Scope() : _variables()
{

}
Scope::~Scope()
{
	for (auto variable : _variables)
	{
		delete variable.second;
	}
}
const IVariable* Scope::getVariable(const std::string& name) const
{
	if (_variables.find(name) == _variables.end())
		throw InterpeterException("Variable " + name + "does not exists");
	return _variables.at(name);
}
void Scope::setVariable(const std::string& name, IVariable* value)
{
	_variables[name] = value;
}
