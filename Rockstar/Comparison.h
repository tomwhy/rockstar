#pragma once
#include "IExpression.h"
#include "Flags.h"

class ComparisonFlags : public Flags
{
public:
	constexpr ComparisonFlags(size_t flags = 0) : Flags(flags) {};
	static const ComparisonFlags less, equal, greater;
};

class Comparison : public IExpression
{
public:
	Comparison(std::shared_ptr<IExpression> left, const ComparisonFlags& op, std::shared_ptr<IExpression> right, bool negate);
	Comparison(const CompiledObject& obj);
	virtual std::shared_ptr<IVariable> evaluate(Scope& scope) const;
	virtual CompiledObject serialize() const;

private:
	std::shared_ptr<IExpression> _left;
	std::shared_ptr<IExpression> _right;
	ComparisonFlags _op;

	bool _negate;
};

