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
std::shared_ptr<VariableName> Utils::createVariableExpression(const Statement& stmt, const std::string& name, const std::string& idx)
{
	Token nameToken = stmt.getToken(name);
	
	if (nameToken.isName("Pronoun"))
	{
		if (stmt.hasToken(idx))
			return std::make_shared<Pronoun>(createExpression(stmt.getToken(idx)));
		else
			return std::make_shared<Pronoun>();
	}
	else if (nameToken.isName("VariableName"))
	{
		if (stmt.hasToken(idx))
			return std::make_shared<VariableName>(nameToken.value(), createExpression(stmt.getToken(idx)));
		else
			return std::make_shared<VariableName>(nameToken.value());
	}

	throw InterpeterException("Not a variable name");
}

std::string Utils::lower(const std::string& str)
{
	std::string res(str);
	std::transform(res.begin(), res.end(), res.begin(), [](char c) {return std::tolower(c); });
	return res;
}