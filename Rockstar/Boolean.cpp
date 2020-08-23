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