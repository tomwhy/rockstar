#include "Comparison.h"
#include "Boolean.h"

constexpr const ComparisonFlags ComparisonFlags::less(1), ComparisonFlags::equal(2), ComparisonFlags::greater(4);

Comparison::Comparison(std::shared_ptr<IExpression> left, const ComparisonFlags& op, std::shared_ptr<IExpression> right, bool negate) :
	_left(left), _op(op), _right(right), _negate(negate)
{
	
}

std::shared_ptr<IVariable> Comparison::evaluate(Scope& scope) const
{
	std::shared_ptr<IVariable> left = _left->evaluate(scope);
	std::shared_ptr<IVariable> right = _right->evaluate(scope);


	bool less = _op & ComparisonFlags::less;
	bool equal = _op & ComparisonFlags::equal;
	bool greater = _op & ComparisonFlags::greater;

	less = less && left->less(right);
	greater = greater && right->less(left);
	equal = equal && left->equal(right);

	return std::make_shared<Boolean>(_negate ^ (less || equal || greater));
}