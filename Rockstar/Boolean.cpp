#include "Boolean.h"

Boolean::Boolean(bool value) : _value(value)
{

}

std::string Boolean::toString()
{
	return _value ? "true" : "false";
}