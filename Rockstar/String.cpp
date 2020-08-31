#include "String.h"
#include "Mysterious.h"
#include "Number.h"
#include "Null.h"
#include "InterpeterExceptions.h"
#include "Utils.h"
#include "Array.h"
#include <cmath>

String::String(const std::string& value) : _value(value), IVariable("String")
{

}
std::string String::toString()
{
	return _value;
}
bool String::toBool()
{
	return !_value.empty();
}

bool String::canBeIndex()
{
	return true;
}

std::shared_ptr<IVariable> String::getAt(const std::string& index)
{
	if (Utils::all<std::string::const_iterator, char>(index.begin(), index.end(), std::isdigit))
	{
		int intIndex = std::stoi(index);
		if (intIndex >= _value.size() || intIndex < 0)
			return std::make_shared<Mysterious>();

		std::string res;
		res.push_back(_value.at(intIndex));

		return std::make_shared<String>(res);
	}

	return std::make_shared<Mysterious>();
}
void String::setAt(const std::string& index, std::shared_ptr<IVariable> value)
{
	throw InterpeterException("String is read-only");
}

std::shared_ptr<IVariable> String::cast(std::shared_ptr<IVariable> arg)
{
	std::string numStr = _value;

	//check if negative
	bool negative = numStr[0] == '-';
	if (negative)
	{
		numStr = numStr.substr(1);
	}

	unsigned int base = 10;
	if (arg != nullptr)
	{
		std::string baseStr = arg->toString();
		if (!Utils::all<std::string::const_iterator, char>(baseStr.begin(), baseStr.end(), std::isdigit))
		{
			throw InterpeterException("Cannot cast with: " + baseStr);
		}

		base = std::stoul(baseStr);

		//check if base is valid
		if (base <= 0)
		{
			throw InterpeterException("Invalid base: " + baseStr);
		}
	}


	//check that there is only one decimal dot (or non at all)
	size_t decimalPoint = numStr.find('.');
	if (decimalPoint != std::string::npos)
	{
		if (numStr.find('.', decimalPoint + 1) != std::string::npos)
		{
			throw InterpeterException("Cannot cast: " + numStr + " to a number");
		}
	}
	else
	{
		decimalPoint = numStr.size();
	}

	//check that there are valid charecters (0-9 for the first ten digits and then a-z for the rest)
	if (base <= 10)
	{
		for (char c : numStr)
		{
			if (c != '.' && (!std::isdigit(c) || (unsigned)(c - '0') >= base))
			{
				throw InterpeterException(c + std::string(" is an invalid charecter for a number in base ") + std::to_string(base));
			}
		}
	}
	else
	{
		for (char c : numStr)
		{
			if (c != '.')
			{
				if (!std::isdigit(c) && (!std::isalpha(c) || (unsigned)(std::tolower(c) - 'a' + 10) >= base)) // convert a letter to it's value
				{
					throw InterpeterException(c + std::string(" is an invalid charecter for a number in base ") + std::to_string(base));
				}
			}
		}
	}

	long double number = 0;

	//convert string to number
	for (int i = 0; i < numStr.size(); i++)
	{
		if (numStr[i] == '.')
			continue;

		long long power = i < decimalPoint ? decimalPoint - i - 1 : decimalPoint - i;
		int digit = std::isdigit(numStr[i]) ? (numStr[i] - '0') : (numStr[i] - 'a' + 10);
		number += digit * std::pow(base, power);
	}

	if (negative)
		number *= -1;

	return std::make_shared<Number>(number);
}

std::shared_ptr<IVariable> String::multiply(std::shared_ptr<IVariable> other)
{
	std::shared_ptr<Number> right = std::dynamic_pointer_cast<Number>(other);
	if (right != nullptr)
	{
		return std::make_shared<String>(Utils::repeat(_value, std::stoi(right->toString())));
	}
	else if (std::dynamic_pointer_cast<Null>(other) != nullptr)
	{
		return std::make_shared<String>(""); // _value * 0 = ""
	}
	else
	{
		return std::make_shared<Mysterious>();
	}
}

std::shared_ptr<IVariable> String::split(std::shared_ptr<IVariable> arg)
{
	std::shared_ptr<IVariable> res;

	if (arg == nullptr)
	{
		res = std::make_shared<Array>("0", getAt("0"));
		for (int i = 1; i < _value.size(); i++)
		{
			std::string idx = std::to_string(i);
			res->setAt(idx, getAt(idx));
		}
	}
	else
	{
		std::string delim = arg->toString();
		size_t offset = 0;
		int idx = 0;
		std::vector<std::string> elements;
		size_t delimLoc;
		do
		{
			delimLoc = _value.find(delim, offset);
			elements.push_back(_value.substr(offset, delimLoc - offset));
			offset = delimLoc + delim.size();
		} while (delimLoc != std::string::npos);

		res = std::make_shared<Array>("0", std::make_shared<String>(elements[0]));
		for (int i = 1; i < elements.size(); i++)
		{
			std::string idx = std::to_string(i);
			res->setAt(idx, std::make_shared<String>(elements[i]));
		}
	}

	return res;
}
