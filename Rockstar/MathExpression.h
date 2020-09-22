#pragma once
#include "IExpression.h"
#include "GenericParser/include/Token.h"


enum class MathOp {Add, Subtract, Multiply, Divide};

class MathExpression : public IExpression
{
public:
	MathExpression(std::shared_ptr<IExpression> left, MathOp op, std::shared_ptr<IExpression> right);
	MathExpression(const CompiledObject& obj);
	virtual std::shared_ptr<IVariable> evaluate(Scope& scope) const;
	virtual CompiledObject serialize() const; 

	static MathOp getOpFromToken(const genericparser::Token& token);
private:
	std::shared_ptr<IExpression> _left;
	MathOp _op;
	std::shared_ptr<IExpression> _right;
};

