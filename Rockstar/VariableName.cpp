#include "VariableName.h"
#include "InterpeterExceptions.h"
#include <algorithm>

VariableName::VariableName(const std::string& name) : VariableName(name, nullptr)
{
}
VariableName::VariableName(const std::string& name, std::shared_ptr<IExpression> index) : _name(name), _index(index)
{

}
VariableName::VariableName(const VariableName& other) : _name(other._name), _index(other._index)
{

}

std::shared_ptr<IVariable> VariableName::evaluate(Scope& scope) const
{
	return scope.getVariable(std::make_shared<VariableName>(*this));
}

bool VariableName::hasIndex() const
{
	return _index != nullptr;
}
std::string VariableName::name(Scope& scope) const
{
	return _name;
}
std::string VariableName::index(Scope& scope) const
{
	if (_index == nullptr)
		throw InterpeterException("Variable " + _name + "does not have an index");

	std::shared_ptr<IVariable> index = _index->evaluate(scope);
	if (!index->canBeIndex())
		throw InterpeterException(index->toString() + " cannot server as an index");
	return index->toString();
}

bool VariableName::isVariable() const
{
	return true;
}