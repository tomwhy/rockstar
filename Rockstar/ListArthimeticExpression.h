#pragma once
#include "MathExpression.h"
class ListArthimeticExpression : public MathExpression
{
public:
	ListArthimeticExpression(std::shared_ptr<IExpression> left, MathOp op, const std::vector<std::shared_ptr<IExpression>>& right);
private:
	static std::shared_ptr<IExpression> reduceVector(MathOp op, std::vector<std::shared_ptr<IExpression>>::const_iterator begin, std::vector<std::shared_ptr<IExpression>>::const_iterator end);
};

