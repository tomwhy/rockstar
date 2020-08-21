#include "ISimpleVariable.h"
#include "InterpeterException.h"

std::shared_ptr<IVariable> ISimpleVariable::getAt(const std::string& index)
{
	throw InterpeterException("not indexable");
}
void ISimpleVariable::setAt(const std::string& index, std::shared_ptr<IVariable> value)
{
	throw InterpeterException("not indexable");
}