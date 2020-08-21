#include "Scope.h"
#include "InterpeterException.h"
#include "Utils.h"
#include "Array.h"

Scope::Scope() : _variables()
{

}
const std::shared_ptr<IVariable> Scope::getVariable(const std::string& name, std::shared_ptr<IExpression> index)
{
	std::string variable = Utils::lower(name);
	if (_variables.find(variable) == _variables.end())
		throw InterpeterException("Variable \"" + name + "\" does not exists");


	_lastVar = variable;
	
	if (index == nullptr)
	{
		return _variables.at(variable);
	}
	
	std::shared_ptr<IVariable> indexVar = index->evaluate(*this);
	
	if (!indexVar->canBeIndex())
	{
		throw InterpeterException(indexVar->toString() + " cannot serve as index");
	}
	else
	{
		return _variables.at(variable)->getAt(indexVar->toString());
	}

}
void Scope::setVariable(const std::string& name, const std::shared_ptr<IVariable> value, std::shared_ptr<IExpression> index)
{
	std::string variable = Utils::lower(name);
	_lastVar = variable;
	if (index == nullptr)
	{
		_variables[variable] = value;
	}
	else
	{
		std::shared_ptr<IVariable> indexVar = index->evaluate(*this);
		if (!indexVar->canBeIndex())
		{
			throw InterpeterException(indexVar->toString() + " cannot serve as index");
		}
		else
		{
			if (_variables.find(variable) == _variables.end())
				_variables[variable] = std::make_shared<Array>(indexVar->toString(), value);
			else
				_variables.at(variable)->setAt(indexVar->toString(), value);
		}
	}

}
std::shared_ptr<IVariable> Scope::getLast() const
{
	if (_lastVar.empty())
		throw InterpeterException("No variable was refrenced");
	return _variables.at(_lastVar);
}