#include "SplitStatement.h"
#include "InterpeterExceptions.h"
#include "ISplitable.h"
#include <vector>

SplitStatement::SplitStatement(std::shared_ptr<IExpression> exp, std::shared_ptr<VariableName> dest, std::shared_ptr<IExpression> argument) :IModifyStatement(exp, dest, argument)
{

}

std::shared_ptr<IVariable> SplitStatement::modify(Scope& scope)
{
	std::shared_ptr<IVariable> value = _exp->evaluate(scope);
	std::shared_ptr<ISplitable> splitable = std::dynamic_pointer_cast<ISplitable>(value);
	if (splitable == nullptr)
		throw TypeException("Cannot split ", value);

	return splitable->split(_argument == nullptr ? nullptr : _argument->evaluate(scope));
}
