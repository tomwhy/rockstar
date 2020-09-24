#pragma once
#include "IExpression.h"
#include "Flags.h"
#include "GenericParser/include/Statement.h"

class ComparisonFlags : public Flags
{
public:
	constexpr ComparisonFlags(size_t flags = 0) : Flags(flags) {};
	static const ComparisonFlags less, equal, greater, negate;
};

class Comparison : public IExpression
{
public:
	Comparison(std::shared_ptr<IExpression> left, const ComparisonFlags& op, std::shared_ptr<IExpression> right);
	Comparison(const CompiledObject& obj);
	virtual std::shared_ptr<IVariable> evaluate(Scope& scope) const;
	virtual CompiledObject serialize() const;

	static ComparisonFlags getOp(const genericparser::Statement& stmt, const std::string& name);

private:
	std::shared_ptr<IExpression> _left;
	std::shared_ptr<IExpression> _right;
	ComparisonFlags _op;

	bool _negate;
};

