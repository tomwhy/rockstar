#include "AssignStatement.h"
#include "Utils.h"
#include "Compiler.h"

AssignStatement::AssignStatement(std::shared_ptr<VariableName> name, std::shared_ptr<IExpression> value) : _var(name), _exp(value)
{

}

AssignStatement::AssignStatement(const AssignStatement& other) : _var(other._var), _exp(other._exp)
{

}
AssignStatement::AssignStatement(const CompiledObject& obj)
{
	if (obj.code() != CompiledObject::ObjectCode::assignmentStmt)
		throw std::runtime_error("Not an assignment statment");
	
	_var = Compiler::parseVariableName(obj.at<CompiledObject>("var"));
	_exp = Compiler::parseCompiledExp(obj.at<CompiledObject>("exp"));
}

void AssignStatement::execute(Scope& scope)
{
	scope.setVariable(_var, _exp->evaluate(scope));
}

CompiledObject AssignStatement::serialize() const
{
	//data will be variable, experssion
	nlohmann::json json;
	json["var"] = _var->serialize();
	json["exp"] = _exp->serialize();

	return CompiledObject(CompiledObject::ObjectCode::assignmentStmt, json);
}