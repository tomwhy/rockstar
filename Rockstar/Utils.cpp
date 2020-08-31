#include "Utils.h"
#include "VariableName.h"
#include "Constant.h"
#include "Pronoun.h"
#include "InterpeterExceptions.h"
#include <algorithm>
#include <sstream>

std::shared_ptr<IExpression> Utils::createExpression(const Statement& stmt, const std::string& name)
{
	if (stmt.contains(name + "_exp_var"))
		return Utils::createVariableExpression(stmt, name + "_exp_var");
	else if (stmt.contains(name + "_math"))
		return Utils::createMathExpression(stmt, name + "_math");
	else if (stmt.contains(name + "_exp"))
	{
		if (!stmt.hasToken(name + "_exp"))
			throw InterpeterException("Could not find the token named: " + name + "_exp");

		Token token = stmt.getToken(name + "_exp");
	
		if (token.isName("Mysterious") || token.isName("Null") || token.isName("Boolean") || token.isName("Number") || token.isName("String"))
		{
			return std::make_shared<Constant>(token);
		}
		else
		{
			throw InterpeterException("Invalid value: " + token.value());
		}
	}
	else
	{
		throw InterpeterException("Invalid Expression");
	}
}
std::shared_ptr<VariableName> Utils::createVariableExpression(const Statement& stmt, const std::string& name)
{	
	Token nameToken = stmt.getToken(name + "_name");
	std::string idx = name + "_idx_exp";

	if (nameToken.isName("Pronoun"))
	{
		if (stmt.hasToken(idx))
			return std::make_shared<Pronoun>(createExpression(stmt, idx));
		else
			return std::make_shared<Pronoun>();
	}
	else if (nameToken.isName("VariableName"))
	{
		if (stmt.hasToken(idx))
			return std::make_shared<VariableName>(nameToken.value(), createExpression(stmt, idx));
		else
			return std::make_shared<VariableName>(nameToken.value());
	}

	throw InterpeterException("Not a variable name");
}

std::shared_ptr<MathExpression> Utils::createMathExpression(const Statement& stmt, const std::string& name)
{
	std::shared_ptr<IExpression> left = Utils::createExpression(stmt, name+"_left"); // left will never be a math expression

	Token opToken = stmt.getToken(name + "_op");
	MathOp op = MathExpression::getOpFromToken(opToken);

	if (stmt.contains(name + "_right_math")) // if the right expression is a Math Expression
	{
		MathOp rightOp = MathExpression::getOpFromToken(stmt.getToken(name + "_right_math_op"));
		if ((op == MathOp::Divide || op == MathOp::Multiply) && (rightOp == MathOp::Add || rightOp == MathOp::Subtract))
		{
			//the current operation is stronger (needs to come first)
			std::shared_ptr<IExpression> right = Utils::createExpression(stmt, name + "_right_math_left"); // take the expression next to the current op
			
			std::shared_ptr<MathExpression> leftEXp = std::make_shared<MathExpression>(left, op, right);
			return std::make_shared<MathExpression>(leftEXp, rightOp, Utils::createExpression(stmt, name + "_right_math_right"));
		}
	}
	else if (stmt.contains(name + "_right_list")) //if the right expression is a list
	{
		return createListExpression(stmt, name + "_right", left, op);
	}
	return std::make_shared<MathExpression>(left, op, Utils::createExpression(stmt, name + "_right"));
}

std::shared_ptr<ListArthimeticExpression> Utils::createListExpression(const Statement& stmt, const std::string& name, std::shared_ptr<IExpression> left, MathOp op)
{
	std::vector<std::shared_ptr<IExpression>> rightVec;
	std::string elem = name + "_list";

	do
	{
		rightVec.push_back(Utils::createExpression(stmt, elem));
		elem += "_next";
	} while (stmt.contains(elem));

	return std::make_shared<ListArthimeticExpression>(left, op, rightVec);
}

std::string Utils::repeat(const std::string& str, int times)
{
	std::stringstream res;
	for (int i = 0; i < times; i++)
	{
		res << str;
	}
	return res.str();
}

std::string Utils::lower(const std::string& str)
{
	std::string res(str);
	std::transform(res.begin(), res.end(), res.begin(), [](char c) {return std::tolower(c); });
	return res;
}