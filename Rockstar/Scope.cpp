#include "Scope.h"
#include "InterpeterException.h"
#include "Utils.h"

Scope::Scope() : _variables()
{

}
const std::shared_ptr<IVariable> Scope::getVariable(const std::string& name) const
{
	std::string variable = Utils::lower(name);
	if (_variables.find(variable) == _variables.end())
		throw InterpeterException("Variable " + name + "does not exists");
	return _variables.at(variable);
}
void Scope::setVariable(const std::string& name, const std::shared_ptr<IVariable> value)
{
	std::string variable = Utils::lower(name);

	_variables[variable] = value;
}
