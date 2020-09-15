#pragma once
#include "ICodeBlock.h"
#include "GenericParser/include/Statement.h"
#include <vector>
#include <iostream>


class RunTime
{
public:
	RunTime(const std::vector<Statement>& statements);
	RunTime();

	void run();
	void run(const Statement& line);

protected:
	std::vector<std::shared_ptr<ICodeBlock>> _code;
	Scope _globalScope;

private:
	std::shared_ptr<ICodeBlock> parseStatment(const Statement& stmt);
};

