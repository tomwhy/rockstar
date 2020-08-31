#include "MathInterfaces.h"
#include "Mysterious.h"

std::shared_ptr<IVariable> StringAddable::add(std::shared_ptr<IVariable> other)
{
	if (std::dynamic_pointer_cast<String>(other) != nullptr)
	{
		return std::make_shared<String>(toString(), other->toString());
	}
	else
	{
		return std::make_shared<Mysterious>();
	}
}