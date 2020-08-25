#include "IncreamentDecreamentStatement.h"
#include "Number.h"
#include "Boolean.h"
#include "InterpeterException.h"

IncreamentDecreamentStatement::IncreamentDecreamentStatement(std::shared_ptr<VariableName> var, size_t count, bool increament) :
	_var(var), _count(count), _increament(increament)
{

}

void IncreamentDecreamentStatement::execute(Scope& scope)
{
	std::shared_ptr<IVariable> var = scope.getVariable(_var);

	if (var->type() == "Number")
	{
		long double value = std::stold(var->toString());
		
		value += _increament ? _count : -(long double)_count;
		
		scope.setVariable(_var, std::make_shared<Number>(value));
	}
	else if (var->type() == "Boolean")
	{
		bool value = var->toBool();
		value = (_count % 2 == 1) ^ value;
		scope.setVariable(_var, std::make_shared<Boolean>(value));
	}
	else
	{
		throw InterpeterException((_increament ? "Increament" : "Decrement") + std::string(" is not supported for ") + var->type());
	}
}