#include "Boolean.h"

Boolean::Boolean(bool value) : _value(value), ISimpleVariable("Boolean")
{

}

bool Boolean::canBeIndex()
{
	return true;
}

std::string Boolean::toString()
{
	return _value ? "true" : "false";
}