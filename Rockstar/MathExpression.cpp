#include "MathExpression.h"
#include "InterpeterException.h"
#include "Number.h"
#include "String.h"
#include "Utils.h"
#include "Mysterious.h"

MathExpression::MathExpression(std::shared_ptr<IExpression> left, MathOp op, std::shared_ptr<IExpression> right) :
	_left(left), _op(op), _right(right)
{

}
MathOp MathExpression::getOpFromToken(const Token& token)
{
	if (token.isName("Add"))
	{
		return MathOp::Add;
	}
	else if (token.isName("Subtract"))
	{
		return MathOp::Subtract;
	}
	else if (token.isName("Multiply"))
	{
		return MathOp::Multiply;
	}
	else if (token.isName("Divide"))
	{
		return MathOp::Divide;
	}
	else
	{
		throw InterpeterException("Invalid Math Op: " + token.value());
	}
}


std::shared_ptr<IVariable> MathExpression::evaluate(Scope& scope) const
{
	switch (_op)
	{
	case MathOp::Add:
		return add(scope);
		break;
	case MathOp::Subtract:
		return subtract(scope);
		break;
	case MathOp::Multiply:
		return multiply(scope);
		break;
	case MathOp::Divide:
		return divide(scope);
		break;
	default:
		throw InterpeterException("Invalid Math operation");
	}
}

std::shared_ptr<IVariable> MathExpression::add(Scope& scope) const
{
	std::shared_ptr<IVariable> left = _left->evaluate(scope);
	std::shared_ptr<IVariable> right = _right->evaluate(scope);

	if (left->type() == "Number" && right->type() == "Number")
	{
		long double res = std::stold(left->toString()) + std::stold(right->toString());
		return std::make_shared<Number>(res);
	}
	else if (left->type() == "String" || right->type() == "String")
	{
		std::string res = left->toString() + right->toString();
		return std::make_shared<String>(res);
	}
	else
	{
		return std::make_shared<Mysterious>();
	}
}
std::shared_ptr<IVariable> MathExpression::subtract(Scope& scope) const
{
	std::shared_ptr<IVariable> left = _left->evaluate(scope);
	std::shared_ptr<IVariable> right = _right->evaluate(scope);

	if (left->type() == "Number" && right->type() == "Number")
	{
		long double res = std::stold(left->toString()) - std::stold(right->toString());
		return std::make_shared<Number>(res);
	}
	else
	{
		return std::make_shared<Mysterious>();
	}
}
std::shared_ptr<IVariable> MathExpression::multiply(Scope& scope) const
{
	std::shared_ptr<IVariable> left = _left->evaluate(scope);
	std::shared_ptr<IVariable> right = _right->evaluate(scope);

	if (left->type() == "Number" && right->type() == "Number")
	{
		long double res = std::stold(left->toString()) * std::stold(right->toString());
		return std::make_shared<Number>(res);
	}
	else
	{
		std::string times;
		std::string str;
		if (left->type() == "Number" && right->type() == "String")
		{
			times = left->toString();
			str = right->toString();
		}
		else if (right->type() == "Number" && left->type() == "String")
		{
			times = right->toString();
			str = left->toString();
		}
		else
		{
			return std::make_shared<Mysterious>();
		}

		if (!(Utils::all<std::string::const_iterator, char>(times.begin(), times.end(), std::isdigit)))
		{
			return std::make_shared<Mysterious>();
		}

		return std::make_shared<String>(Utils::repeat(str, std::stoi(times)));
	}
}
std::shared_ptr<IVariable> MathExpression::divide(Scope& scope) const
{
	std::shared_ptr<IVariable> left = _left->evaluate(scope);
	std::shared_ptr<IVariable> right = _right->evaluate(scope);

	if (left->type() == "Number" && right->type() == "Number")
	{
		if (right->toString() == "0")
		{
			return std::make_shared<Mysterious>();
		}
		long double res = std::stold(left->toString()) / std::stold(right->toString());
		return std::make_shared<Number>(res);
	}
	else
	{
		return std::make_shared<Mysterious>();
	}
}