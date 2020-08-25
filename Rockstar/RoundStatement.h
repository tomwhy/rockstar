#pragma once
#include "VariableName.h"
#include "ICodeBlock.h"
#include "GenericParser/include/Token.h"

enum class RoundOp {Up, Down, Nearest};

class RoundStatement : public ICodeBlock
{
public:
	RoundStatement(std::shared_ptr<VariableName> var, RoundOp op);
	virtual void execute(Scope& scope);

	static RoundOp getOpFromToken(const Token& token);
private:
	std::shared_ptr<VariableName> _var; 
	RoundOp _op;
};

