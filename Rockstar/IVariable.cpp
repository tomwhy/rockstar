#include "IVariable.h"
#include "String.h"
#include "Mysterious.h"
#include "Boolean.h"
#include "InterpeterExceptions.h"

std::shared_ptr<IVariable> IVariable::add(std::shared_ptr<IVariable> other)
{
	if (std::dynamic_pointer_cast<String>(other) != nullptr)
	{
		return std::make_shared<String>(toString() + other->toString());
	}
	else
	{
		return std::make_shared<Mysterious>();
	}
}

bool IVariable::equal(std::shared_ptr<IVariable> other)
{
	throw InterpeterException("Equality comparison is not allowed between " + _typeName + " and " + other->_typeName);
}

bool IVariable::less(std::shared_ptr<IVariable> other)
{
	throw InterpeterException("Ordering comparison is not allowed between " + _typeName + " and " + other->_typeName);
}
