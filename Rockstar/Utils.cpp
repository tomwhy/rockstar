#include "Utils.h"
#include "VariableName.h"
#include "Constant.h"
#include "InterpeterException.h"

const IExpression* Utils::createExpression(const Token& token)
{
	if (token.isName("Variable"))
		return new VariableName(token.value());
	else if (token.isName("Literal"))
		return new Constant(token);
	else
		throw InterpeterException("Invalid value: " + token.value());
}