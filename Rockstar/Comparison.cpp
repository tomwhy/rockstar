#include "Comparison.h"
#include "Boolean.h"
#include "Utils.h"
#include "Compiler.h"

constexpr const ComparisonFlags ComparisonFlags::less(1), ComparisonFlags::equal(2), ComparisonFlags::greater(4);

Comparison::Comparison(std::shared_ptr<IExpression> left, const ComparisonFlags& op, std::shared_ptr<IExpression> right, bool negate) :
	_left(left), _op(op), _right(right), _negate(negate)
{
	
}
Comparison::Comparison(const CompiledObject& obj)
{
	if (obj.code() != CompiledObject::ObjectCode::compareExp)
		throw std::runtime_error("Not a comparison expression");

	_left = Compiler::parseCompiledExp(obj.at<CompiledObject>("left"));
	_right = Compiler::parseCompiledExp(obj.at<CompiledObject>("right"));
	_op = obj.at<ComparisonFlags>("op");
	_negate = obj.at<bool>("neg");
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

CompiledObject Comparison::serialize() const
{
	// data will be left, op (size_t), right
	nlohmann::json json;
	json["left"] = _left->serialize();
	json["op"] = _op;
	json["right"] = _right->serialize();
	json["neg"] = _negate;

	return CompiledObject(CompiledObject::ObjectCode::compareExp, json);
}