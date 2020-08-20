#pragma once
#include "Scope.h"

class ICodeBlock
{
public:
	virtual ~ICodeBlock() {};
	virtual void execute(Scope& scope) = 0;
};