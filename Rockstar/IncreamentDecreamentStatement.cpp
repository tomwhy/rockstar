#include "IncreamentDecreamentStatement.h"
#include "IIncreametable.h"
#include "InterpeterExceptions.h"
#include "Utils.h"
#include "Compiler.h"

IncreamentDecreamentStatement::IncreamentDecreamentStatement(std::shared_ptr<VariableName> var, size_t count, bool increament) :
	_var(var), _count(count), _increament(increament)
{

}
IncreamentDecreamentStatement::IncreamentDecreamentStatement(const CompiledObject& obj)
{
	if (obj.code() != CompiledObject::ObjectCode::incDecStmt)
		throw std::runtime_error("Not an increament/decreament statement");

	_var = Compiler::parseVariableName(obj.at<CompiledObject>("var"));
	_count = obj.at<size_t>("count");
	_increament = obj.at<bool>("increament");
}


void IncreamentDecreamentStatement::execute(Scope& scope)
{
	std::shared_ptr<IVariable> var = scope.getVariable(_var);
	std::shared_ptr<IIncreameantable> increamentable = std::dynamic_pointer_cast<IIncreameantable>(var);

	if (increamentable != nullptr)
	{
		if (_increament)
		{
			increamentable->increament(_count);
		}
		else
		{
			increamentable->decreament(_count);
		}

	}
	else
	{
		throw TypeException((_increament ? "Increament" : "Decrement") + std::string(" is not supported for "), var);
	}
}

CompiledObject IncreamentDecreamentStatement::serialize() const
{
	nlohmann::json json;
	json["var"] = _var->serialize();
	json["count"] = _count;
	json["increament"] = _increament;

	return CompiledObject(CompiledObject::ObjectCode::incDecStmt, json);
}