#include "PrintStatement.h"
#include "Utils.h"
#include "Compiler.h"
#include <iostream>

PrintStatement::PrintStatement(std::shared_ptr<IExpression> exp) : _exp(exp)
{
	
}
PrintStatement::PrintStatement(const CompiledObject& obj)
{
	if (obj.code() != CompiledObject::ObjectCode::printStmt)
		throw std::runtime_error("Not a print statement");

	_exp = Compiler::parseCompiledExp(obj.at<CompiledObject>("exp"));
}
void PrintStatement::execute(Scope& scope)
{
	std::cout << _exp->evaluate(scope)->toString() << std::endl;
}
CompiledObject PrintStatement::serialize() const
{
	nlohmann::json json;
	json["exp"] = _exp->serialize();

	return CompiledObject(CompiledObject::ObjectCode::printStmt, json);
}