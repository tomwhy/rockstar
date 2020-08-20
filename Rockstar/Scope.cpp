#include "Scope.h"
#include "InterpeterException.h"
#include "Utils.h"

Scope::Scope() : _variables()
{

}
const std::shared_ptr<IVariable> Scope::getVariable(const std::string& name)
{
	std::string variable = Utils::lower(name);
	if (_variables.find(variable) == _variables.end())
		throw InterpeterException("Variable \"" + name + "\" does not exists");
	_lastVar = variable;
	return _variables.at(variable);
}
void Scope::setVariable(const std::string& name, const std::shared_ptr<IVariable> value)
{
	std::string variable = Utils::lower(name);
	_lastVar = variable;
	_variables[variable] = value;
}
std::shared_ptr<IVariable> Scope::getLast() const
{
	if (_lastVar.empty())
		throw InterpeterException("No variable was refrenced");
	return _variables.at(_lastVar);
}