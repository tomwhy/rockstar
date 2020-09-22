#include "IModifyStatement.h"
#include "InterpeterExceptions.h"
#include "Compiler.h"

IModifyStatement::IModifyStatement(std::shared_ptr<IExpression> exp, std::shared_ptr<VariableName> dest, std::shared_ptr<IExpression> argument) : 
	_exp(exp), _dest(dest), _argument(argument)
{
}
IModifyStatement::IModifyStatement(const CompiledObject& obj) :
	IModifyStatement(Compiler::parseCompiledExp(obj.at<CompiledObject>("exp")), 
		obj.contains("dest") ? Compiler::parseVariableName(obj.at<CompiledObject>("dest")) : nullptr,
		obj.contains("arg") ? Compiler::parseCompiledExp(obj.at<CompiledObject>("arg")) : nullptr)
{

}

void IModifyStatement::execute(Scope& scope)
{
	if (_dest == nullptr && !_exp->isVariable())
		throw InterpeterException("Cannot modify literal in place");

	std::shared_ptr<IVariable> newValue = modify(scope);

	if (_dest != nullptr)
		scope.setVariable(_dest, newValue);
	else
		scope.setVariable(std::dynamic_pointer_cast<VariableName>(_exp), newValue); //this is a bit hacky selution. a better one is welcome	
}

nlohmann::json IModifyStatement::serializeExpressions() const
{
	nlohmann::json json;
	json["exp"] = _exp->serialize();

	if (_dest != nullptr)
		json["dest"] = _dest->serialize();

	if (_argument != nullptr)
		json["arg"] = _argument->serialize();

	return json;
}
