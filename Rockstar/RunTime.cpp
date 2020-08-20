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
		return std::make_shared<AssignStatement>(stmt.getToken("var").value(), Utils::createExpression(stmt.getToken("value")));
	else if (stmt.name() == "Print")
		return std::make_shared<PrintStatement>(Utils::createExpression(stmt.getToken("value")));
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
