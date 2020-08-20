#include "Number.h"

Number::Number(double value) : _value(value)
{

}

std::string Number::toString()
{
	return std::to_string(_value);
}