#pragma once
#include "VariableName.h"
#include "ICodeBlock.h"
#include "GenericParser/include/Token.h"

enum class RoundOp {Up, Down, Nearest};

class RoundStatement : public ICodeBlock
{
public:
	RoundStatement(std::shared_ptr<VariableName> var, RoundOp op);
	RoundStatement(const CompiledObject& obj);
	virtual void execute(Scope& scope);
	virtual CompiledObject serialize() const;


	static RoundOp getOpFromToken(const genericparser::Token& token);
private:
	std::shared_ptr<VariableName> _var; 
	RoundOp _op;
};

