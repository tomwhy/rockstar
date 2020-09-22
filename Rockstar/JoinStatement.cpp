#include "JoinStatement.h"
#include "InterpeterExceptions.h"
#include "IJoinable.h"
#include "Utils.h"

JoinStatement::JoinStatement(std::shared_ptr<IExpression> exp, std::shared_ptr<VariableName> dest, std::shared_ptr<IExpression> argument) :
	IModifyStatement(exp, dest, argument)
{

}
JoinStatement::JoinStatement(const CompiledObject& obj) : IModifyStatement(checkObjectCode(obj))
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

CompiledObject JoinStatement::serialize() const
{

	return CompiledObject(CompiledObject::ObjectCode::joinStmt, serializeExpressions());
}
CompiledObject JoinStatement::checkObjectCode(const CompiledObject& obj)
{
	if (obj.code() != CompiledObject::ObjectCode::joinStmt)
		throw std::runtime_error("Not a cast statement");
	return obj;
}