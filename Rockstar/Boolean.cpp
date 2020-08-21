#include "Boolean.h"

Boolean::Boolean(bool value) : _value(value)
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