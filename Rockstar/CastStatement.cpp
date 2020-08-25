#include "CastStatement.h"
#include "InterpeterException.h"
#include "Utils.h"
#include "Number.h"
#include "String.h"
#include <cmath>
#include <sstream>

CastStatement::CastStatement(std::shared_ptr<IExpression> exp, std::shared_ptr<VariableName> dest, std::shared_ptr<IExpression> argument) :IModifyStatement(exp, dest, argument)
{

}

std::shared_ptr<IVariable> CastStatement::modify(Scope& scope)
{
	std::shared_ptr<IVariable> value = _exp->evaluate(scope);

	if (value->type() == "String")
	{
		std::string numStr = value->toString();
		bool negative = numStr[0] == '-';
		if (negative)
		{
			numStr = numStr.substr(1);
		}
		unsigned int base = 10;
		std::string baseStr = std::to_string(base);
		if (_argument != nullptr)
		{
			baseStr = _argument->evaluate(scope)->toString();
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
					throw InterpeterException(c + std::string(" is an invalid charecter for a number in base ") + baseStr);
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
						throw InterpeterException(c + std::string(" is an invalid charecter for a number in base ") + baseStr);
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

			size_t power = i < decimalPoint ? decimalPoint - i - 1 : decimalPoint - i;
			int digit = std::isdigit(numStr[i]) ? (numStr[i] - '0') : (numStr[i] - 'a' + 10);
			number += digit * std::pow(base, power);
		}

		if (negative)
			number *= -1;

		return std::make_shared<Number>(number);
	}
	else if (value->type() == "Number")
	{
		std::string valueStr = value->toString();
		if (!Utils::all<std::string::const_iterator, char>(valueStr.begin(), valueStr.end(), std::isdigit))
		{
			throw InterpeterException("Cannot convert " + valueStr + " to string");
		}

		std::ostringstream res;
		res << static_cast<char>(std::stoi(valueStr));
		return std::make_shared<String>(res.str());
	}
	else
	{
		throw InterpeterException("Can only cast strings and numbers");
	}
}