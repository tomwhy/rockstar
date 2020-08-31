#include "RoundStatement.h"
#include "Mysterious.h"
#include "IRoundable.h"
#include "InterpeterExceptions.h"
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
	std::shared_ptr<IRoundable> value = std::dynamic_pointer_cast<IRoundable>(_var->evaluate(scope));
	if (value == nullptr)
	{
		scope.setVariable(_var, std::make_shared<Mysterious>());
		return;
	}

	switch (_op)
	{
	case RoundOp::Up:
		value->ceil();
		break;
	case RoundOp::Down:
		value->floor();
		break;
	case RoundOp::Nearest:
		value->round();
		break;
	default:
		throw InterpeterException("Invalid rounding operation");
		break;
	}
}