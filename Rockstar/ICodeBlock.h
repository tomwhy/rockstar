#pragma once
#include "Scope.h"

class ICodeBlock
{
public:
	virtual ~ICodeBlock() {};
	ICodeBlock() = default;
	ICodeBlock(const ICodeBlock& other) {};
	virtual void execute(Scope& scope) = 0;
};