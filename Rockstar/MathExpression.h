#pragma once
#include "IExpression.h"
#include "GenericParser/include/Token.h"

enum class MathOp {Add, Subtract, Multiply, Divide};

class MathExpression : public IExpression
{
public:
	MathExpression(std::shared_ptr<IExpression> left, MathOp op, std::shared_ptr<IExpression> right);
	virtual std::shared_ptr<IVariable> evaluate(Scope& scope) const;

	static MathOp getOpFromToken(const Token& token);

private:
	std::shared_ptr<IExpression> _left;
	MathOp _op;
	std::shared_ptr<IExpression> _right;
};

