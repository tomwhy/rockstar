#pragma once
#include "Scope.h"

class ICodeBlock
{
public:
	virtual void execute(Scope& scope) = 0;
};