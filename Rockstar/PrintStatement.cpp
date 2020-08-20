#include "PrintStatement.h"
#include <iostream>

PrintStatement::PrintStatement(std::shared_ptr<IExpression> exp) : _exp(exp)
{

}
void PrintStatement::execute(Scope& scope)
{
	std::cout << _exp->evaluate(scope)->toString() << std::endl;
}