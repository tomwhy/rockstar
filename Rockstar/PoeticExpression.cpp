#include "PoeticExpression.h"
#include <sstream>
#include <algorithm>

PoeticExpression::PoeticExpression(const Token& token, bool stringLiteral) : Constant(parseLiteral(token, stringLiteral))
{

}

Token PoeticExpression::parseLiteral(const Token& token, bool stringLiteral)
{
	if (!token.isName("PoeticLiteral"))
		return token;

	if (stringLiteral)
		return Token("String", { {0, '"' + token.value() + '"' } });

	std::stringstream value(token.value());
	std::string word;

	std::stringstream res;
	bool decimalPlaces = false;

	while (std::getline(value, word, ' '))
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