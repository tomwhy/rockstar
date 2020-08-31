#include "Boolean.h"
#include "Mysterious.h"

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