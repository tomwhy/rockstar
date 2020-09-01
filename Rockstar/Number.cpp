#include "Number.h"
#include "String.h"
#include "Null.h"
#include "Mysterious.h"
#include "Boolean.h"
#include "Array.h"
#include "Utils.h"
#include "InterpeterExceptions.h"
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

std::shared_ptr<IVariable> Number::cast(std::shared_ptr<IVariable> arg)
{
	if (std::trunc(_value) != _value)  // trunc returns the whole part of a floating point number
	{
		throw InterpeterException("Cannot convert " + toString() + " to string");
	}

	std::ostringstream res;
	res << static_cast<char>((int)_value);
	return std::make_shared<String>(res.str());
}

void Number::increament(size_t count)
{
	_value += count;
}
void Number::decreament(size_t count)
{
	_value -= count;
}

std::shared_ptr<IVariable> Number::add(std::shared_ptr<IVariable> other)
{
	if (std::dynamic_pointer_cast<Number>(other) != nullptr) //Number + Number
	{
		std::shared_ptr<Number> right = std::dynamic_pointer_cast<Number>(other);

		return std::make_shared<Number>(_value + right->_value);
	}
	else if (std::dynamic_pointer_cast<Null>(other) != nullptr)
	{
		return std::make_shared<Number>(_value); // _value + 0 = _value
	}
	else
	{
		return IVariable::add(other);
	}
}
std::shared_ptr<IVariable> Number::subtract(std::shared_ptr<IVariable> other)
{
	if (std::dynamic_pointer_cast<Number>(other) != nullptr) //Number - Number
	{
		std::shared_ptr<Number> right = std::dynamic_pointer_cast<Number>(other);

		return std::make_shared<Number>(_value - right->_value);
	}
	else if (std::dynamic_pointer_cast<Null>(other) != nullptr)
	{
		return std::make_shared<Number>(_value); // _value - 0 = _value
	}
	else
	{
		return std::make_shared<Mysterious>();
	}
}
std::shared_ptr<IVariable> Number::multiply(std::shared_ptr<IVariable> other)
{
	if (std::dynamic_pointer_cast<Number>(other) != nullptr) //Number + Number
	{
		std::shared_ptr<Number> right = std::dynamic_pointer_cast<Number>(other);

		return std::make_shared<Number>(_value * right->_value);
	}
	else if (std::dynamic_pointer_cast<String>(other) != nullptr) //Number + String
	{
		std::shared_ptr<String> right = std::dynamic_pointer_cast<String>(other);

		return std::make_shared<String>(Utils::repeat(right->toString(), (long)_value));
	}
	else if (std::dynamic_pointer_cast<Null>(other) != nullptr)
	{
		return std::make_shared<Number>(0); // _value * 0 = 0
	}
	else
	{
		return std::make_shared<Mysterious>();
	}
}
std::shared_ptr<IVariable> Number::divide(std::shared_ptr<IVariable> other)
{
	if (std::dynamic_pointer_cast<Number>(other) != nullptr) //Number + Number
	{
		std::shared_ptr<Number> right = std::dynamic_pointer_cast<Number>(other);
		
		if(right == 0)
			throw InterpeterException("divition by zero error");

		return std::make_shared<Number>(_value / right->_value);
	}
	else if (std::dynamic_pointer_cast<Null>(other) != nullptr)
	{
		throw InterpeterException("divition by zero error");
	}
	else
	{
		return std::make_shared<Mysterious>();
	}
}

void Number::ceil()
{
	_value = std::ceil(_value);
}
void Number::floor()
{
	_value = std::floor(_value);
}
void Number::round()
{
	_value = std::round(_value);
}

bool Number::equal(std::shared_ptr<IVariable> other)
{
	if (std::dynamic_pointer_cast<Mysterious>(other) != nullptr)
	{
		return false;
	}
	else if (std::dynamic_pointer_cast<String>(other) != nullptr)
	{
		try
		{
			long double right = std::stold(other->toString());

			return _value == right;
		}
		catch(const std::invalid_argument&)
		{
			return false;
		}
	}
	else if (std::dynamic_pointer_cast<Boolean>(other) != nullptr)
	{
		return toBool() == other->toBool();
	}
	else if (std::dynamic_pointer_cast<Null>(other) != nullptr)
	{
		return _value == 0;
	}
	else if (std::dynamic_pointer_cast<Array>(other) != nullptr)
	{
		return _value == std::stoull(std::dynamic_pointer_cast<Array>(other)->toString());
	}
	else //number
	{
		return _value == std::dynamic_pointer_cast<Number>(other)->_value;
	}
}

bool Number::less(std::shared_ptr<IVariable> other)
{
	if (std::dynamic_pointer_cast<String>(other) != nullptr)
	{
		try
		{
			long double right = std::stold(other->toString());

			return _value < right;
		}
		catch (const std::invalid_argument&)
		{
			return false;
		}
	}
	else if (std::dynamic_pointer_cast<Array>(other) != nullptr)
	{
		return _value < std::stoull(std::dynamic_pointer_cast<Array>(other)->toString());
	}
	else if(std::dynamic_pointer_cast<Number>(other) != nullptr)
	{
		return _value < std::dynamic_pointer_cast<Number>(other)->_value;
	}
	else if (std::dynamic_pointer_cast<Null>(other) != nullptr)
	{
		return _value < 0;
	}
	else
	{
		return IVariable::less(other);
	}
}