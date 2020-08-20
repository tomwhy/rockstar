#include "VariableName.h"

VariableName::VariableName(const std::string& name) : _name(name)
{

}
std::shared_ptr<IVariable> VariableName::evaluate(Scope& scope) const
{
	return scope.getVariable(_name);
}