#include "SplitStatement.h"
#include "InterpeterExceptions.h"
#include "ISplitable.h"
#include "Utils.h"
#include <vector>

SplitStatement::SplitStatement(std::shared_ptr<IExpression> exp, std::shared_ptr<VariableName> dest, std::shared_ptr<IExpression> argument) :IModifyStatement(exp, dest, argument)
{

}
SplitStatement::SplitStatement(const CompiledObject& obj) : IModifyStatement(checkObjectCode(obj))
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

CompiledObject SplitStatement::serialize() const
{
	return CompiledObject(CompiledObject::ObjectCode::splitStmt, serializeExpressions());
}

CompiledObject SplitStatement::checkObjectCode(const CompiledObject& obj)
{
	if (obj.code() != CompiledObject::ObjectCode::splitStmt)
		throw std::runtime_error("Not a cast statement");
	return obj;
}