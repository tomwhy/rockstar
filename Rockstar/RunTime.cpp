#include "RunTime.h"
#include "AssignStatement.h"
#include "Constant.h"
#include "InterpeterException.h"

RunTime::RunTime(const std::vector<Statement>& statements) : _globalScope()
{
	for (auto statement : statements)
	{
		
	}
}

ICodeBlock* RunTime::parseStatment(const Statement& stmt)
{
	if (stmt.name() == "Assign")
		return new AssignStatement(stmt.getToken("var").value(), new Constant(stmt.getToken("val")));
	else
		throw InterpeterException("Unknow statment: " + stmt.name());
}

RunTime::~RunTime()
{
	for (ICodeBlock* statement : _code)
	{
		delete statement;
	}
}

void RunTime::run()
{
	for (ICodeBlock* statement : _code)
	{
		statement->execute(_globalScope);
	}
}
