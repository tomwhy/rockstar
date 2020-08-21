#include "VariableName.h"
#include <algorithm>

VariableName::VariableName(const std::string& name) : VariableName(name, nullptr)
{
}
VariableName::VariableName(const std::string& name, std::shared_ptr<IExpression> index) : _name(name), _index(index)
{

}
std::shared_ptr<IVariable> VariableName::evaluate(Scope& scope) const
{
	return scope.getVariable(_name, _index);
}