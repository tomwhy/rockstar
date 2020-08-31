#include "IncreamentDecreamentStatement.h"
#include "IIncreametable.h"
#include "InterpeterExceptions.h"

IncreamentDecreamentStatement::IncreamentDecreamentStatement(std::shared_ptr<VariableName> var, size_t count, bool increament) :
	_var(var), _count(count), _increament(increament)
{

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