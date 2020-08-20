#include "Number.h"

Number::Number(double value) : _value(value)
{

}

std::string Number::toString()
{
	std::string res = std::to_string(_value);
	
	res = res.substr(0, res.find_last_not_of('0') + 1); // remove tailing zeroes
	if (res.find('.') == res.size() - 1) //if there are no zeroes left then remove the decimal point
		res = res.substr(0, res.size() - 1);

	return res;
}