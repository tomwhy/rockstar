#include "Utils.h"
#include "VariableName.h"
#include "Constant.h"
#include "Pronoun.h"
#include "LogicNotExpression.h"
#include "InterpeterExceptions.h"
#include "GenericParser/include/PossibilityIterator.h"
#include "GenericParser/include/tinyxml2/tinyxml2.h"
#include <algorithm>
#include <sstream>
#include <numeric>
#include <Windows.h>

#define ROCKSTAR_DEFS "RockstarDefs.xml"

std::shared_ptr<IExpression> Utils::createExpression(const genericparser::Statement& stmt, const std::string& name)
{
	if (stmt.contains(name + "_exp_var"))
	{
		return Utils::createVariableExpression(stmt, name + "_exp_var");
	}
	else if (stmt.contains(name + "_math"))
	{
		return Utils::createMathExpression(stmt, name + "_math");
	}
	else if (stmt.contains(name + "_comp"))
	{
		return Utils::createComparisonExpression(stmt, name + "_comp");
	}
	else if (stmt.contains(name + "_logicNot"))
	{
		return std::make_shared<LogicNotExpression>(Utils::createExpression(stmt, name + "_logicNot_right"));
	}
	else if (stmt.contains(name + "_exp"))
	{
		if (!stmt.hasToken(name + "_exp"))
			throw InterpeterException("Could not find the token named: " + name + "_exp");

		genericparser::Token token = stmt.getToken(name + "_exp");
	
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
std::shared_ptr<VariableName> Utils::createVariableExpression(const genericparser::Statement& stmt, const std::string& name)
{	
	genericparser::Token nameToken = stmt.getToken(name + "_name");
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
		if (stmt.contains(idx))
			return std::make_shared<VariableName>(nameToken.value(), createExpression(stmt, idx));
		else
			return std::make_shared<VariableName>(nameToken.value());
	}

	throw InterpeterException("Not a variable name");
}
std::shared_ptr<Comparison> Utils::createComparisonExpression(const genericparser::Statement& stmt, const std::string& name)
{
	std::shared_ptr<IExpression> left = Utils::createExpression(stmt, name + "_left");
	ComparisonFlags op = Comparison::getOp(stmt, name);

	if (stmt.contains(name + "_right_comp")) // there is another compere expression to the right
	{
		//comparisons are left assosiative (grouped to the left)
		left = std::make_shared<Comparison>(left, op, Utils::createExpression(stmt, name + "_right_comp_left"));
		op = Comparison::getOp(stmt, name + "_right_comp");
		return std::make_shared<Comparison>(left, op, Utils::createExpression(stmt, name + "_right_comp_right"));
	}
	else
	{
		return std::make_shared<Comparison>(left, op, Utils::createExpression(stmt, name + "_right"));
	}
}
std::shared_ptr<MathExpression> Utils::createMathExpression(const genericparser::Statement& stmt, const std::string& name)
{
	std::shared_ptr<IExpression> left = Utils::createExpression(stmt, name+"_left"); // left will never be a math expression

	genericparser::Token opToken = stmt.getToken(name + "_op");
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
std::shared_ptr<ListArthimeticExpression> Utils::createListExpression(const genericparser::Statement& stmt, const std::string& name, std::shared_ptr<IExpression> left, MathOp op)
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

genericparser::Statement Utils::parseExpression(const std::vector<genericparser::Token>& line, const std::string& name)
{
	tinyxml2::XMLDocument xml;
	xml.LoadFile(getDefsPath().c_str());
	tinyxml2::XMLElement* root = xml.FirstChildElement();
	tinyxml2::XMLElement* defines = root->FirstChildElement("defines");
	
	genericparser::OrPossibilityIterator it(line, defines->FirstChildElement("Value"), defines);

	genericparser::Statement s("Remaining");

	while (it.getNext())
	{
		genericparser::Possibility p = it.current();
		if (p.tokens.size() == line.size())
		{
			for (auto& t : p.tokens)
			{
				if (!t.second.empty())
				{
					s.addToken(name + "_" + t.second, t.first);
				}
				else
				{
					s.addToken(name, t.first);

				}
			}

			return s;
		}
	}

	throw std::runtime_error("Invalid expression: " + std::accumulate(line.begin(), line.end(), std::string(""), [](const std::string& res, const genericparser::Token& t) {return res + t.value(false); }));
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

std::string Utils::getDefsPath()
{
	char path[MAX_PATH] = { 0 };

	GetModuleFileNameA(NULL, path, MAX_PATH);

	std::string defsPath(path);
	defsPath = defsPath.substr(0, defsPath.find_last_of("\\/") + 1) + ROCKSTAR_DEFS;

	return defsPath;
}