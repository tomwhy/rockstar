#include "Comparison.h"
#include "Boolean.h"
#include "Utils.h"
#include "Compiler.h"

constexpr const ComparisonFlags ComparisonFlags::less(1), ComparisonFlags::equal(2), ComparisonFlags::greater(4), ComparisonFlags::negate(8);

Comparison::Comparison(std::shared_ptr<IExpression> left, const ComparisonFlags& op, std::shared_ptr<IExpression> right) :
	_left(left), _op(op), _right(right), _negate(_op & ComparisonFlags::negate)
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

ComparisonFlags Comparison::getOp(const genericparser::Statement& stmt, const std::string& name)\
{
	std::string negatePath = name;
	ComparisonFlags op;

	if (stmt.contains(name + "_equ"))
	{
		negatePath += "_equ_neg";
		op |= ComparisonFlags::equal;
	}
	else if (stmt.contains(name + "_order equ"))
	{
		negatePath += "_order equ_neg";
		op |= ComparisonFlags::equal | (stmt.getToken(name + "_order equ_order").isName("High") ? ComparisonFlags::greater : ComparisonFlags::less);
	}
	else
	{
		negatePath += "_order_neg";
		op |= (stmt.getToken(name + "_order_order").isName("Higher") ? ComparisonFlags::greater : ComparisonFlags::less);
	}

	if (stmt.getToken(negatePath).isName("Isnt"))
	{
		op |= ComparisonFlags::negate;
	}

	return op;
}