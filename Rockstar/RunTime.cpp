#include "RunTime.h"
#include "AssignStatement.h"
#include "PrintStatement.h"
#include "SplitStatement.h"
#include "Constant.h"
#include "InterpeterException.h"
#include "Utils.h"

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
	if (stmt.name() == "Assign")
	{
		return std::make_shared<AssignStatement>(Utils::createVariableExpression(stmt, "var"), Utils::createExpression(stmt, "value"));
	}
	else if (stmt.name() == "Print")
	{
		return std::make_shared<PrintStatement>(Utils::createExpression(stmt, "value"));
	}
	else if (stmt.name() == "Modify")
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
		else
		{
			throw InterpeterException("Unknown modify op: " + stmt.getToken("op").value());
		}
	}
	else if (stmt.name() == "EndBlock")
	{
		return nullptr;
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
