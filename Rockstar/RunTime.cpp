#include "RunTime.h"
#include "AssignStatement.h"
#include "PrintStatement.h"
#include "SplitStatement.h"
#include "JoinStatement.h"
#include "CastStatement.h"
#include "IncreamentDecreamentStatement.h"
#include "RoundStatement.h"
#include "Constant.h"
#include "PoeticExpression.h"
#include "InterpeterExceptions.h"
#include "Utils.h"
#include <regex>

RunTime::RunTime(const std::vector<Statement>& statements) : _globalScope()
{
	for (auto statement : statements)
	{
		std::shared_ptr<ICodeBlock> line = parseStatment(statement);
		if(line != nullptr)
			_code.push_back(line);
	}
}

std::shared_ptr<ICodeBlock> RunTime::parseStatment(const Statement& stmt)
{
	std::string stmtName = stmt.name();
	if (stmtName == "Assign")
	{
		std::shared_ptr<IExpression> value;
		if (stmt.contains("compound")) //compound assignment
		{
			std::shared_ptr<VariableName> var = Utils::createVariableExpression(stmt, "var");
			MathOp op = MathExpression::getOpFromToken(stmt.getToken("compound_op"));

			if (stmt.hasToken("compound_list"))
			{
				value = Utils::createListExpression(stmt, "compound", var, op);
			}
			else
			{
				value = std::make_shared<MathExpression>(var, op, Utils::createExpression(stmt, "compound_value"));
			}
		}
		else
		{
			value = Utils::createExpression(stmt, "value");
		}
		return std::make_shared<AssignStatement>(Utils::createVariableExpression(stmt, "var"), value);
	}
	else if (stmtName == "PoeticAssign")
	{
		std::shared_ptr<VariableName> var = Utils::createVariableExpression(stmt, "var");
		if (stmt.getToken("op").isName("Says"))
		{
			return std::make_shared<AssignStatement>(var, std::make_shared<PoeticExpression>(stmt.getToken("literal").value(), true));
		}
		else
		{
			if (stmt.contains("literal_val"))
			{
				return std::make_shared<AssignStatement>(var, Utils::createExpression(stmt, "literal_val"));
			}
			else if(stmt.contains("literal_literal"))
			{
				return std::make_shared<AssignStatement>(var, Utils::createExpression(stmt, "literal_literal"));
			}
			else
			{
				std::string str;
				str = stmt.getToken("literal_start").value() + " " + stmt.getToken("literal_end").value();

				return std::make_shared<AssignStatement>(var, std::make_shared<PoeticExpression>(str, false));
			}
		}
	}
	else if (stmtName == "Print")
	{
		return std::make_shared<PrintStatement>(Utils::createExpression(stmt, "value"));
	}
	else if (stmtName == "Modify")
	{
		std::shared_ptr<IExpression> exp;
		std::shared_ptr<VariableName> dest;
		std::shared_ptr<IExpression> argument;
		
		exp = Utils::createExpression(stmt, "exp");
		
		if (stmt.contains("dest"))
			dest = Utils::createVariableExpression(stmt, "dest");

		if (stmt.contains("arg"))
		{
			argument = Utils::createExpression(stmt, "arg");
		}
		


		if (stmt.getToken("op").isName("Cut"))
		{
			return std::make_shared<SplitStatement>(exp, dest, argument);
		}
		else if (stmt.getToken("op").isName("Join"))
		{
			return std::make_shared<JoinStatement>(exp, dest, argument);
		}
		else if (stmt.getToken("op").isName("Cast"))
		{
			return std::make_shared<CastStatement>(exp, dest, argument);
		}
		else
		{
			throw InterpeterException("Unknown modify op: " + stmt.getToken("op").value());
		}
	}
	else if (stmtName == "EndBlock")
	{
		return nullptr;
	}
	else if (stmtName == "Increament" || stmtName == "Decreament")
	{
		std::string temp = stmt.getToken("count").value();
		std::regex regex(R"(\w+)");
		int count = (int)std::distance(std::sregex_iterator(temp.begin(), temp.end(), regex), std::sregex_iterator());

		return std::make_shared<IncreamentDecreamentStatement>(Utils::createVariableExpression(stmt, "var"), count, stmtName == "Increament");
	}
	else if (stmtName == "Rounding")
	{
		return std::make_shared<RoundStatement>(Utils::createVariableExpression(stmt, "var"), RoundStatement::getOpFromToken(stmt.getToken("op")));
	}
	else
		throw InterpeterException("Unknow statment: " + stmt.name());
}

void RunTime::run()
{
	for (std::shared_ptr<ICodeBlock> statement : _code)
	{
		statement->execute(_globalScope);
	}
}
