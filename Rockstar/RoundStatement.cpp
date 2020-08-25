#include "RoundStatement.h"
#include "Mysterious.h"
#include "Number.h"
#include "InterpeterException.h"
#include <cmath>

RoundStatement::RoundStatement(std::shared_ptr<VariableName> var, RoundOp op) : _var(var), _op(op)
{

}

RoundOp RoundStatement::getOpFromToken(const Token& token)
{
	if (token.isName("Up"))
		return RoundOp::Up;
	else if (token.isName("Down"))
		return RoundOp::Down;
	else if (token.isName("Round"))
		return RoundOp::Nearest;
	else
		throw InterpeterException("Invalid Round Op: " + token.value());
}

void RoundStatement::execute(Scope& scope)
{
	std::shared_ptr<IVariable> value = _var->evaluate(scope);
	if (value->type() != "Number")
	{
		scope.setVariable(_var, std::make_shared<Mysterious>());
		return;
	}

	long double number = std::stold(value->toString());
	long double result = 0;
	switch (_op)
	{
	case RoundOp::Up:
		result = std::ceil(number);
		break;
	case RoundOp::Down:
		result = std::floor(number);
		break;
	case RoundOp::Nearest:
		result = std::round(number);
		break;
	default:
		throw InterpeterException("Invalid rounding operation");
		break;
	}

	scope.setVariable(_var, std::make_shared<Number>(result));
}