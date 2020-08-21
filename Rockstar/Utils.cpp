#include "Utils.h"
#include "VariableName.h"
#include "Constant.h"
#include "Pronoun.h"
#include "InterpeterException.h"
#include <algorithm>

std::shared_ptr<IExpression> Utils::createExpression(const Token& token)
{
	if (token.isName("Pronoun"))
	{
		return std::make_shared<Pronoun>();
	}
	else if (token.isName("VariableName"))
	{
		return std::make_shared<VariableName>(token.value());
	}		
	else if (token.isName("Mysterious") || token.isName("Null") || token.isName("Boolean") || token.isName("Number") || token.isName("String"))
	{
		return std::make_shared<Constant>(token);
	}
	else
	{
		throw InterpeterException("Invalid value: " + token.value());
	}
}
std::shared_ptr<IExpression> Utils::createVariableExpression(const Token& name, const Token& index)
{
	if (name.isName("Pronoun"))
	{
		return std::make_shared<Pronoun>(createExpression(index));
	}
	else if (name.isName("VariableName"))
	{
		return std::make_shared<VariableName>(name.value(), createExpression(index));
	}

	throw InterpeterException("Not a variable name");
}

std::string Utils::lower(const std::string& str)
{
	std::string res(str);
	std::transform(res.begin(), res.end(), res.begin(), [](char c) {return std::tolower(c); });
	return res;
}