#pragma once
#include "Scope.h"

class ICodeBlock
{
public:
	virtual void execute(const Scope& scope) = 0;
};