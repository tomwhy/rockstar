#include "Boolean.h"
#include "Mysterious.h"
#include "String.h"
#include "Number.h"

Boolean::Boolean(bool value) : _value(value), ISimpleVariable("Boolean")
{

}

bool Boolean::canBeIndex()
{
	return true;
}

bool Boolean::toBool()
{
	return _value;
}

std::string Boolean::toString()
{
	return _value ? "true" : "false";
}

void Boolean::increament(size_t count)
{
	_value = (count % 2 == 1) ^ _value;
}
void Boolean::decreament(size_t count)
{
	increament(count); //increament and decreament on boolean are the same
}

bool Boolean::equal(std::shared_ptr<IVariable> other)
{
	if(std::dynamic_pointer_cast<Mysterious>(other) == nullptr)
		return _value == other->toBool();

	return false;
}