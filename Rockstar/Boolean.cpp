#include "Boolean.h"

Boolean::Boolean(bool value) : _value(value), ISimpleVariable("Boolean")
{

}

bool Boolean::canBeIndex()
{
	return false;
}

std::string Boolean::toString()
{
	return _value ? "true" : "false";
}