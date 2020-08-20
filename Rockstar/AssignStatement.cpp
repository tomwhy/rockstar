#include "AssignStatement.h"

AssignStatement::AssignStatement(const std::string& name, const IExpression* value) : _name(name), _exp(value)
{

}
AssignStatement::~AssignStatement()
{
	delete _exp;
}
void AssignStatement::execute(Scope& scope)
{
	scope.setVariable(_name, _exp->evaluate(scope));
}
