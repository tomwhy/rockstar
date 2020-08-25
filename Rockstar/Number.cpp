#include "Number.h"
#include <sstream>
#include <iomanip>

Number::Number(long double value) : _value(value), ISimpleVariable("Number")
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
	//convert the value with precision of 10 digits after the decimal dot
	std::string res = (std::ostringstream() << std::fixed <<std::setprecision(10) << _value).str();
	
	res = res.substr(0, res.find_last_not_of('0') + 1); // remove tailing zeroes
	if (res.find('.') == res.size() - 1) //if there are no zeroes left then remove the decimal point
		res = res.substr(0, res.size() - 1);

	return res;
}
