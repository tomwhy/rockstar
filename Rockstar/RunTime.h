#pragma once
#include "ICodeBlock.h"
#include "GenericParser/include/Statement.h"
#include <vector>

class RunTime
{
public:
	RunTime(const std::vector<Statement>& statements);

	void run();
private:
	static std::shared_ptr<ICodeBlock> parseStatment(const Statement& stmt);

	std::vector<std::shared_ptr<ICodeBlock>> _code;
	Scope _globalScope;
};

