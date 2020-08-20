#include "VariableName.h"

VariableName::VariableName(const std::string& name) : _name(name)
{

}
const IVariable* VariableName::evaluate(Scope& scope) const
{
	return scope.getVariable(_name);
}