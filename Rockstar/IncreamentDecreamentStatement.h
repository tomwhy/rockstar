#pragma once
#include "ICodeBlock.h"
class IncreamentDecreamentStatement : public ICodeBlock
{
public:
	IncreamentDecreamentStatement(std::shared_ptr<VariableName> var, size_t count, bool increament);
	IncreamentDecreamentStatement(const CompiledObject& obj);
	virtual void execute(Scope& scope);
	virtual CompiledObject serialize() const;
private:
	std::shared_ptr<VariableName> _var;
	size_t _count;
	bool _increament;
};

