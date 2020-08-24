#include "Number.h"

Number::Number(double value) : _value(value), ISimpleVariable("Number")
{

}

bool Number::canBeIndex()
{
	return true;
}

bool Number::toBool()
{
	return _value != 0;
}

std::string Number::toString()
{
	std::string res = std::to_string(_value);
	
	res = res.substr(0, res.find_last_not_of('0') + 1); // remove tailing zeroes
	if (res.find('.') == res.size() - 1) //if there are no zeroes left then remove the decimal point
		res = res.substr(0, res.size() - 1);

	return res;
}

void Number::increament()
{
	_value+=1;
}
void Number::decreament()
{
	_value-=1;
}