#include "JoinStatement.h"
#include "InterpeterExceptions.h"
#include "IJoinable.h"

JoinStatement::JoinStatement(std::shared_ptr<IExpression> exp, std::shared_ptr<VariableName> dest, std::shared_ptr<IExpression> argument) :
	IModifyStatement(exp, dest, argument)
{

}

std::shared_ptr<IVariable> JoinStatement::modify(Scope& scope)
{
	std::shared_ptr<IVariable> value = _exp->evaluate(scope);
	std::shared_ptr<IJoinable> joinable = std::dynamic_pointer_cast<IJoinable>(value);
	
	if (value == nullptr)
		throw TypeException("Cannot Join ", value);

	return joinable->join(_argument == nullptr ? nullptr : _argument->evaluate(scope));
}
