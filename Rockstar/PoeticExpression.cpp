#include "PoeticExpression.h"
#include <sstream>
#include <algorithm>

PoeticExpression::PoeticExpression(const std::string& string, bool stringLiteral) : Constant(parseLiteral(string, stringLiteral))
{

}

Token PoeticExpression::parseLiteral(const std::string& value, bool stringLiteral)
{
	if (stringLiteral)
		return Token("String", { {0, '"' + value + '"' } });

	std::stringstream valueStream(value);
	std::string word;

	std::stringstream res;
	bool decimalPlaces = false;

	while (std::getline(valueStream, word, ' '))
	{
		int digit = 0;

		if (!decimalPlaces)
		{
			size_t dotOffset;
			if ((dotOffset = word.find('.')) != std::string::npos)
			{
				if (dotOffset != 0)
				{
					digit = std::count_if(word.begin(), word.begin() + dotOffset, [](char c) {return c == '-' || std::isalpha(c); }) % 10;
					res << digit;
				}

				res << '.';
				
				if (dotOffset != word.size() - 1)
				{
					digit = std::count_if(word.begin() + dotOffset, word.end(), [](char c) {return c == '-' || std::isalpha(c); }) % 10;
					res << digit;
				}

				decimalPlaces = true;
			}
			else
			{
				digit = std::count_if(word.begin(), word.end(), [](char c) {return c == '-' || std::isalpha(c); }) % 10;
				res << digit;
			}
		}
		else
		{
			digit = std::count_if(word.begin(), word.end(), [](char c) {return c == '-' || std::isalpha(c); }) % 10;
			res << digit;
		}
		
	}

	return Token("Number", {{0, res.str()}});
}