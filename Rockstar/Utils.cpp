#include "Utils.h"
#include "VariableName.h"
#include "Constant.h"
#include "InterpeterException.h"
#include <algorithm>

std::shared_ptr<IExpression> Utils::createExpression(const Token& token)
{
	if (token.isName("Variable"))
		return std::make_shared<VariableName>(token.value());
	else if (token.isName("Literal"))
		return std::make_shared<Constant>(token);
	else
		throw InterpeterException("Invalid value: " + token.value());
}
std::string Utils::lower(const std::string& str)
{
	std::string res(str);
	std::transform(res.begin(), res.end(), res.begin(), [](char c) {return std::tolower(c); });
	return res;
}