#include "Utils.h"
#include "VariableName.h"
#include "Constant.h"
#include "Pronoun.h"
#include "InterpeterException.h"
#include <algorithm>

std::shared_ptr<IExpression> Utils::createExpression(const Statement& stmt, const std::string& name)
{
	if (stmt.hasToken(name + "_var"))
		return Utils::createVariableExpression(stmt, name);

	if (!stmt.hasToken(name))
		throw InterpeterException("Could not find the token named: " + name);

	Token token = stmt.getToken(name);
	
	if (token.isName("Mysterious") || token.isName("Null") || token.isName("Boolean") || token.isName("Number") || token.isName("String"))
	{
		return std::make_shared<Constant>(token);
	}
	else
	{
		throw InterpeterException("Invalid value: " + token.value());
	}
}
std::shared_ptr<VariableName> Utils::createVariableExpression(const Statement& stmt, const std::string& name)
{
	Token nameToken = stmt.getToken(name + "_var");
	std::string idx = name + "_idx_exp";

	if (nameToken.isName("Pronoun"))
	{
		if (stmt.hasToken(idx))
			return std::make_shared<Pronoun>(createExpression(stmt, idx));
		else
			return std::make_shared<Pronoun>();
	}
	else if (nameToken.isName("VariableName"))
	{
		if (stmt.hasToken(idx))
			return std::make_shared<VariableName>(nameToken.value(), createExpression(stmt, idx));
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