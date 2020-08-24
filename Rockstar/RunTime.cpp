#include "RunTime.h"
#include "AssignStatement.h"
#include "PrintStatement.h"
#include "SplitStatement.h"
#include "JoinStatement.h"
#include "CastStatement.h"
#include "IncreamentDecreamentStatement.h"
#include "Constant.h"
#include "InterpeterException.h"
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
		return std::make_shared<AssignStatement>(Utils::createVariableExpression(stmt, "var"), Utils::createExpression(stmt, "value"));
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
		
		if (stmt.hasToken("dest_var"))
			dest = Utils::createVariableExpression(stmt, "dest");

		try
		{
			argument = Utils::createExpression(stmt, "arg");
		}
		catch (const InterpeterException&)
		{

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
		int count = std::distance(std::sregex_iterator(temp.begin(), temp.end(), regex), std::sregex_iterator());

		return std::make_shared<IncreamentDecreamentStatement>(Utils::createVariableExpression(stmt, "var"), count, stmtName == "Increament");
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
