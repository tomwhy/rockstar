#include "AssignStatement.h"

AssignStatement::AssignStatement(const std::string& name, std::shared_ptr<IExpression> value) : _name(name), _exp(value)
{

}
void AssignStatement::execute(Scope& scope)
{
	scope.setVariable(_name, _exp->evaluate(scope));
}
