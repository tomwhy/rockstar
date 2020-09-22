#include "MathExpression.h"
#include "InterpeterExceptions.h"
#include "MathInterfaces.h"
#include "Utils.h"
#include "Mysterious.h"
#include "Compiler.h"

MathExpression::MathExpression(std::shared_ptr<IExpression> left, MathOp op, std::shared_ptr<IExpression> right) :
	_left(left), _op(op), _right(right)
{

}
MathExpression::MathExpression(const CompiledObject& obj)
{
	if (obj.code() != CompiledObject::ObjectCode::mathExp)
		throw std::runtime_error("Not a math expression");

	_left = Compiler::parseCompiledExp(obj.at<CompiledObject>("left"));
	_right = Compiler::parseCompiledExp(obj.at<CompiledObject>("right"));
	_op = obj.at<MathOp>("op");
}

MathOp MathExpression::getOpFromToken(const genericparser::Token& token)
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

CompiledObject MathExpression::serialize() const
{
	// data will be left, op (char), right
	nlohmann::json json;
	json["left"] = _left->serialize();
	json["op"] = _op;
	json["right"] = _right->serialize();

	return CompiledObject(CompiledObject::ObjectCode::mathExp, json);
}