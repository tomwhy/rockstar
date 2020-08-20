#pragma once
#include "ICodeBlock.h"
#include "GenericParser/include/Statement.h"
#include <vector>

class RunTime
{
public:
	RunTime(const std::vector<Statement>& statements);
	~RunTime();

	void run();
private:
	static ICodeBlock* parseStatment(const Statement& stmt);

	std::vector<ICodeBlock*> _code;
	Scope _globalScope;
};

