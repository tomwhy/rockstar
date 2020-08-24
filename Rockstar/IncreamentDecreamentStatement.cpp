#include "IncreamentDecreamentStatement.h"

IncreamentDecreamentStatement::IncreamentDecreamentStatement(std::shared_ptr<VariableName> var, size_t count, bool increament) :
	_var(var), _count(count), _increament(increament)
{

}

void IncreamentDecreamentStatement::execute(Scope& scope)
{
	std::shared_ptr<IVariable> value = scope.getVariable(_var);

	if (_increament)
	{
		for (int i = 0; i < _count; i++)
			value->increament();
	}
	else
	{
		for (int i = 0; i < _count; i++)
			value->decreament();
	}
}