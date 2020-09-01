#include "Mysterious.h"
#include "InterpeterExceptions.h"

Mysterious::Mysterious() : ISimpleVariable("Mysterious")
{

}
std::string Mysterious::toString()
{
	return "mysterious";
}
bool Mysterious::canBeIndex()
{
	return false;
}
bool Mysterious::toBool()
{
	return false;
}

bool Mysterious::equal(std::shared_ptr<IVariable> other)
{
	if (std::dynamic_pointer_cast<Mysterious>(other) != nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}
