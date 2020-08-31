#include "MathExpression.h"
#include "InterpeterExceptions.h"
#include "MathInterfaces.h"
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
	std::shared_ptr<IVariable> left = _left->evaluate(scope);
	std::shared_ptr<IVariable> right = _right->evaluate(scope);

	switch (_op)
	{
	case MathOp::Add:
		return left->add(right);
		break;
	case MathOp::Subtract:
	{
		std::shared_ptr<ISubtractable> subtractable = std::dynamic_pointer_cast<ISubtractable>(left);
		if (subtractable != nullptr)
			return subtractable->subtract(right);
		break;
	}
	case MathOp::Multiply:
	{
		std::shared_ptr<IMultiplyable> multiplyable = std::dynamic_pointer_cast<IMultiplyable>(left);
		if (multiplyable != nullptr)
			return multiplyable->multiply(right);
		break;
	}
	case MathOp::Divide:
	{
		std::shared_ptr<IDivieable> divideable = std::dynamic_pointer_cast<IDivieable>(left);
		if (divideable != nullptr)
			return divideable->divide(right);
		break;
	}
	default:
		throw InterpeterException("Invalid Math operation");
	}

	return std::make_shared<Mysterious>();
}