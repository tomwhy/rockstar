#include "Scope.h"
#include "InterpeterException.h"

Scope::Scope() : _variables()
{

}
const std::shared_ptr<IVariable> Scope::getVariable(const std::string& name) const
{
	if (_variables.find(name) == _variables.end())
		throw InterpeterException("Variable " + name + "does not exists");
	return _variables.at(name);
}
void Scope::setVariable(const std::string& name, const std::shared_ptr<IVariable> value)
{
	_variables[name] = value;
}
