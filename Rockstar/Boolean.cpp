#include "Boolean.h"

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

void Boolean::increament()
{
	_value = !_value;
}
void Boolean::decreament()
{
	_value = !_value;
}