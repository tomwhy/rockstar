#include "AssignStatement.h"

AssignStatement::AssignStatement(const std::string& name, std::shared_ptr<IExpression> value) : _name(name), _exp(value)
{

}
AssignStatement::AssignStatement(const std::string& name, std::shared_ptr<IExpression> index, std::shared_ptr<IExpression> value) : _name(name), _exp(value), _index(index)
{

}
void AssignStatement::execute(Scope& scope)
{
	scope.setVariable(_name, _exp->evaluate(scope), _index);
}
