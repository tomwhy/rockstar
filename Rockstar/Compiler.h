#pragma once
#include <string>
#include <fstream>
#include "GenericParser/include/Parser.h"
#include "ICodeBlock.h"


class Compiler
{
public:
	Compiler(const std::string& file);

	const std::vector<std::unique_ptr<ICodeBlock>>& getCode();
	
	static std::unique_ptr<ICodeBlock> parseCompiledCode(const CompiledObject& obj);
	static std::shared_ptr<IExpression> parseCompiledExp(const CompiledObject& obj);
	static std::shared_ptr<VariableName> parseVariableName(const CompiledObject& obj);

private:
	void compileFile(const std::string& file);
	
	static CompiledObject readCompiledBlock(std::ifstream& file);

	std::unique_ptr<ICodeBlock> parseStatment(const genericparser::Statement& stmt);

	std::vector<std::unique_ptr<ICodeBlock>> _code;
	genericparser::Parser _parser;
};

