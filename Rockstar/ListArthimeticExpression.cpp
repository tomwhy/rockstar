#include "ListArthimeticExpression.h"
#include "InterpeterExceptions.h"
#include <functional>

ListArthimeticExpression::ListArthimeticExpression(std::shared_ptr<IExpression> left, MathOp op, const std::vector<std::shared_ptr<IExpression>>& right) :
	MathExpression(left, op, reduceVector(op, right.begin(), right.end()))
{
	
}

std::shared_ptr<IExpression> ListArthimeticExpression::reduceVector(MathOp op, std::vector<std::shared_ptr<IExpression>>::const_iterator begin, std::vector<std::shared_ptr<IExpression>>::const_iterator end)
{
	if (begin + 1 == end)
	{
		return begin[0];
	}
	else
	{
		if (op == MathOp::Subtract) // left - right1 - right2 - ... = left - (right1 + right2 + ...)
			op = MathOp::Add;
		else if (op == MathOp::Divide) // left / right1 / right 2 / ... = left / (right1 * right2 * ...)
			op = MathOp::Multiply;

		return std::make_shared<MathExpression>(begin[0], op, reduceVector(op, begin + 1, end));
	}
}