#include "CastStatement.h"
#include "InterpeterExceptions.h"
#include "Utils.h"
#include "ICastable.h"
#include <cmath>
#include <sstream>

CastStatement::CastStatement(std::shared_ptr<IExpression> exp, std::shared_ptr<VariableName> dest, std::shared_ptr<IExpression> argument) :IModifyStatement(exp, dest, argument)
{

}

std::shared_ptr<IVariable> CastStatement::modify(Scope& scope)
{
	std::shared_ptr<IVariable> exp = _exp->evaluate(scope);
	std::shared_ptr<ICastable> value = std::dynamic_pointer_cast<ICastable>(exp);

	if (value != nullptr)
	{
		return value->cast(_argument == nullptr ? nullptr : _argument->evaluate(scope));
	}
	else
	{
		throw TypeException("Cannot cast ", exp);
	}
}