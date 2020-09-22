#pragma once
#include "ICodeBlock.h"
#include "GenericParser/include/Statement.h"
#include <vector>
#include <iostream>


class RunTime
{
public:
	RunTime();

	void run(const std::vector<std::unique_ptr<ICodeBlock>>& code);
	void run(std::unique_ptr<ICodeBlock> line);

private:
	Scope _globalScope;
};

