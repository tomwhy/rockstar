#include "IModifyStatement.h"
#include "InterpeterException.h"

IModifyStatement::IModifyStatement(std::shared_ptr<IExpression> exp, std::shared_ptr<VariableName> dest, std::shared_ptr<IExpression> argument) : 
	_exp(exp), _dest(dest), _argument(argument)
{
	if (dest == nullptr && !_exp->isVariable())
		throw InterpeterException("Cannot modify literal in place");
}
void IModifyStatement::execute(Scope& scope)
{
	std::shared_ptr<IVariable> newValue = modify();

	if (_dest != nullptr)
		scope.setVariable(_dest, newValue);
	else
		scope.setVariable(std::dynamic_pointer_cast<VariableName>(_exp), newValue); //this is a bit hacky selution. a better one is welcome	
}