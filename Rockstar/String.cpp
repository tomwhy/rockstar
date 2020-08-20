#include "String.h"

String::String(const std::string& value) : _value(value)
{

}

std::string String::toString()
{
	return _value;
}