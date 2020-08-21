#include "AssignStatement.h"

AssignStatement::AssignStatement(std::shared_ptr<VariableName> name, std::shared_ptr<IExpression> value) : _var(name), _exp(value)
{

}

AssignStatement::AssignStatement(const AssignStatement& other) : _var(other._var), _exp(other._exp)
{

}

void AssignStatement::execute(Scope& scope)
{
	if (_var->hasIndex())
		scope.setVariable(_var, _exp->evaluate(scope));
}
