#include "RunTime.h"
#include "AssignStatement.h"
#include "PrintStatement.h"
#include "Constant.h"
#include "InterpeterException.h"
#include "Utils.h"

RunTime::RunTime(const std::vector<Statement>& statements) : _globalScope()
{
	for (auto statement : statements)
	{
		_code.push_back(parseStatment(statement));
	}
}

std::shared_ptr<ICodeBlock> RunTime::parseStatment(const Statement& stmt)
{
	if (stmt.name() == "Assign")
	{
		if (stmt.hasToken("var_idx_exp"))
		{
			return std::make_shared<AssignStatement>(stmt.getToken("var_var").value(), Utils::createExpression(stmt.getToken("var_idx_exp")), Utils::createExpression(stmt.getToken("value")));
		}
		else
		{
			return std::make_shared<AssignStatement>(stmt.getToken("var_var").value(), Utils::createExpression(stmt.getToken("value")));
		}
	}
	else if (stmt.name() == "Print")
	{
		if (stmt.hasToken("value_var") && stmt.hasToken("value_idx_exp"))
			return std::make_shared<PrintStatement>(Utils::createVariableExpression(stmt.getToken("value_var"), stmt.getToken("value_idx_exp")));
		else if (stmt.hasToken("value_var"))
			return std::make_shared<PrintStatement>(Utils::createExpression(stmt.getToken("value_var")));
		else
			return std::make_shared<PrintStatement>(Utils::createExpression(stmt.getToken("value")));
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
