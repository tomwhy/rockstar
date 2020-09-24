#include "LogicNotExpression.h"
#include "Compiler.h"
#include "Boolean.h"

LogicNotExpression::LogicNotExpression(std::shared_ptr<IExpression> exp) : _exp(exp)
{

}
LogicNotExpression::LogicNotExpression(const CompiledObject& obj)
{
	if (obj.code() != CompiledObject::ObjectCode::notExp)
		throw std::runtime_error("Not a logical not expression");

	_exp = Compiler::parseCompiledExp(obj.at<CompiledObject>("exp"));
}
std::shared_ptr<IVariable> LogicNotExpression::evaluate(Scope& scope) const
{
	return std::make_shared<Boolean>(!_exp->evaluate(scope)->toBool());
}
CompiledObject LogicNotExpression::serialize() const
{
	nlohmann::json json;
	json["exp"] = _exp->serialize();

	return CompiledObject(CompiledObject::ObjectCode::notExp, json);
}