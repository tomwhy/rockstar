#include "JoinStatement.h"
#include "InterpeterException.h"
#include "String.h"

JoinStatement::JoinStatement(std::shared_ptr<IExpression> exp, std::shared_ptr<VariableName> dest, std::shared_ptr<IExpression> argument) :
	IModifyStatement(exp, dest, argument)
{

}

std::shared_ptr<IVariable> JoinStatement::modify(Scope& scope)
{
	std::shared_ptr<IVariable> value = _exp->evaluate(scope);
	if (value->type() != "Array")
		throw InterpeterException("Can only join arrays");

	std::string res;
	std::string delim = _argument == nullptr ? "" : _argument->evaluate(scope)->toString();
	
	size_t arraySize = std::stoul(value->toString());
	for (int i = 0; i < arraySize; i++)
	{
		std::shared_ptr<IVariable> valueAtIndex = value->getAt(std::to_string(i));
		if (valueAtIndex->type() != "Mysterious" && valueAtIndex->type() != "Null")
		{
			res += valueAtIndex->toString() + delim;
		}
	}

	return std::make_shared<String>(res);
}
