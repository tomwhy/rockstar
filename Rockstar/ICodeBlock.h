#pragma once
#include "Scope.h"
#include "CompiledObject.h"

class ICodeBlock
{
public:
	virtual ~ICodeBlock() {};
	ICodeBlock() = default;
	ICodeBlock(const ICodeBlock& other) {};
	virtual void execute(Scope& scope) = 0;
	virtual CompiledObject serialize() const = 0;
};