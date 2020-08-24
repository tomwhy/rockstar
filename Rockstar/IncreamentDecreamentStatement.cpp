#include "IncreamentDecreamentStatement.h"

IncreamentDecreamentStatement::IncreamentDecreamentStatement(std::shared_ptr<VariableName> var, size_t count, bool increament) :
	_var(var), _count(count), _increament(increament)
{

}
void IncreamentDecreamentStatement::execute(Scope& scope)
{
}
