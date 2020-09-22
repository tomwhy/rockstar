#include "Scope.h"
#include "InterpeterExceptions.h"
#include "Utils.h"
#include "Array.h"
#include "VariableName.h"

Scope::Scope() : _variables()
{

}
const std::shared_ptr<IVariable> Scope::getVariable(std::shared_ptr<VariableName> var)
{
	std::string name = var->name(*this);

	std::string variable = Utils::lower(name);
	if (_variables.find(variable) == _variables.end())
		throw InterpeterException("Variable \"" + name + "\" does not exists");


	_lastVar = variable;
	
	if (!var->hasIndex())
	{
		return _variables.at(variable);
	}
	
	
	return _variables.at(variable)->getAt(var->index(*this));

}
void Scope::setVariable(std::shared_ptr<VariableName> var, const std::shared_ptr<IVariable> value)
{
	std::string name = var->name(*this);
	std::string variable = Utils::lower(name);
	_lastVar = variable;
	if (!var->hasIndex())
	{
		_variables[variable] = value;
	}
	else
	{
		if (_variables.find(variable) == _variables.end())
			_variables[variable] = std::make_shared<Array>(var->index(*this), value);
		else
			_variables.at(variable)->setAt(var->index(*this), value);	
	}

}
std::shared_ptr<IVariable> Scope::getLast() const
{
	if (_lastVar.empty())
		throw InterpeterException("No variable was refrenced");
	return _variables.at(_lastVar);
}

std::string Scope::getLastName() const
{
	return _lastVar;
}

std::map<std::string, std::shared_ptr<IVariable>> Scope::getVariables() const
{
	return _variables;
}