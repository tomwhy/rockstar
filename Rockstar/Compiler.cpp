#include "Compiler.h"
#include "Utils.h"
#include "PreProcessor.h"
#include "AssignStatement.h"
#include "PrintStatement.h"
#include "SplitStatement.h"
#include "JoinStatement.h"
#include "CastStatement.h"
#include "IncreamentDecreamentStatement.h"
#include "RoundStatement.h"
#include "Constant.h"
#include "Pronoun.h"
#include "PoeticExpression.h"
#include "InterpeterExceptions.h"
#include <regex>
#include <filesystem>
#include <numeric>

#define CACHE_DIR ".rock"
#define COMPILED_ROCK_EXT ".crock"

Compiler::Compiler(const std::string& file) :  _parser(Utils::getDefsPath()), _code()
{
	compileFile(file);
}

const std::vector<std::unique_ptr<ICodeBlock>>& Compiler::getCode()
{
	return _code;
}

void Compiler::compileFile(const std::string& file)
{
	std::filesystem::path filePath(file);
	std::filesystem::path compiledFilePath = filePath.parent_path() / CACHE_DIR;

	if (!std::filesystem::exists(compiledFilePath))
	{
		std::filesystem::create_directories(compiledFilePath);
	}
	compiledFilePath /= filePath.stem().string() + COMPILED_ROCK_EXT;

	if (std::filesystem::exists(compiledFilePath) && std::filesystem::last_write_time(compiledFilePath) > std::filesystem::last_write_time(filePath))
	{
		//the compiled file is up to date. parse the compiled file instead of the file
		
		std::ifstream compiledFile(compiledFilePath.string(), std::ios::in | std::ios::binary);
		compiledFile.seekg(0, std::ios::end);
		std::streampos endPos = compiledFile.tellg();
		compiledFile.seekg(0, std::ios::beg);

		while (compiledFile.tellg() < endPos)
		{
			_code.push_back(parseCompiledCode(readCompiledBlock(compiledFile)));
		}
	}
	else
	{
		//the compiled file is not up to date. recompile the program

		std::vector<genericparser::Statement> statements = _parser.parse(PreProcessor::readLines(file));
		std::ofstream compiledFile(compiledFilePath.string(), std::ios::out | std::ios::binary);

		for (genericparser::Statement& stmt : statements)
		{
			std::unique_ptr<ICodeBlock> line = parseStatment(stmt);

			std::vector<uint8_t> serializedLine = line->serialize().getCompiledObject();
			compiledFile.write((char*)serializedLine.data(), serializedLine.size());
			_code.push_back(std::move(line));
		}

	}
}

std::unique_ptr<ICodeBlock> Compiler::parseStatment(const genericparser::Statement& stmt)
{
	std::string stmtName = stmt.name();
	if (stmtName == "Assign")
	{
		std::shared_ptr<IExpression> value;
		if (stmt.contains("compound")) //compound assignment
		{
			std::shared_ptr<VariableName> var = Utils::createVariableExpression(stmt, "var");
			MathOp op = MathExpression::getOpFromToken(stmt.getToken("compound_op"));

			if (stmt.contains("compound_list"))
			{
				value = Utils::createListExpression(stmt, "compound", var, op);
			}
			else
			{
				value = std::make_shared<MathExpression>(var, op, Utils::createExpression(stmt, "compound_value"));
			}
		}
		else
		{
			value = Utils::createExpression(stmt, "value");
		}
		return std::make_unique<AssignStatement>(Utils::createVariableExpression(stmt, "var"), value);
	}
	else if (stmtName == "PoeticAssign")
	{
		std::shared_ptr<VariableName> var = Utils::createVariableExpression(stmt, "var");
		std::vector<genericparser::Token> literals = stmt.getTokens("literal");
		if (stmt.getToken("op").isName("Says"))
		{
			std::string value = std::accumulate(literals.begin(), literals.end(), std::string(), [](const std::string& res, genericparser::Token& t) {return res + t.value(false); });

			return std::make_unique<AssignStatement>(var, std::make_shared<PoeticExpression>(value, true));
		}
		else
		{
			if (literals[0].isName("Literal"))
			{
				return std::make_unique<AssignStatement>(var, Utils::createExpression(Utils::parseExpression(literals, "literal"), "literal"));
			}
			else
			{
				std::string value = std::accumulate(literals.begin(), literals.end(), std::string(), [](const std::string& res, genericparser::Token& t) {return res + t.value(false); });

				return std::make_unique<AssignStatement>(var, std::make_shared<PoeticExpression>(value, false));
			}
		}
	}
	else if (stmtName == "Print")
	{
		return std::make_unique<PrintStatement>(Utils::createExpression(stmt, "value"));
	}
	else if (stmtName == "Modify")
	{
		std::shared_ptr<IExpression> exp;
		std::shared_ptr<VariableName> dest;
		std::shared_ptr<IExpression> argument;

		exp = Utils::createExpression(stmt, "exp");

		if (stmt.contains("dest"))
			dest = Utils::createVariableExpression(stmt, "dest");

		if (stmt.contains("arg"))
		{
			argument = Utils::createExpression(stmt, "arg");
		}



		if (stmt.getToken("op").isName("Cut"))
		{
			return std::make_unique<SplitStatement>(exp, dest, argument);
		}
		else if (stmt.getToken("op").isName("Join"))
		{
			return std::make_unique<JoinStatement>(exp, dest, argument);
		}
		else if (stmt.getToken("op").isName("Cast"))
		{
			return std::make_unique<CastStatement>(exp, dest, argument);
		}
		else
		{
			throw InterpeterException("Unknown modify op: " + stmt.getToken("op").value());
		}
	}
	else if (stmtName == "EndBlock")
	{
		return nullptr;
	}
	else if (stmtName == "Increament" || stmtName == "Decreament")
	{
		std::string temp = stmt.getToken("count").value();
		std::regex regex(R"(\w+)");
		int count = (int)std::distance(std::sregex_iterator(temp.begin(), temp.end(), regex), std::sregex_iterator());

		return std::make_unique<IncreamentDecreamentStatement>(Utils::createVariableExpression(stmt, "var"), count, stmtName == "Increament");
	}
	else if (stmtName == "Rounding")
	{
		return std::make_unique<RoundStatement>(Utils::createVariableExpression(stmt, "var"), RoundStatement::getOpFromToken(stmt.getToken("op")));
	}
	else
		throw InterpeterException("Unknow statment: " + stmt.name());
}

CompiledObject Compiler::readCompiledBlock(std::ifstream& file)
{
	size_t size = 0;
	file.read((char*)&size, sizeof(size_t));



	std::vector<char> data(size);
	file.read(data.data(), size);

	return CompiledObject(std::vector<uint8_t>(data.begin(), data.end()));
}

std::unique_ptr<ICodeBlock> Compiler::parseCompiledCode(const CompiledObject& obj)
{
	switch (obj.code())
	{
	case CompiledObject::ObjectCode::assignmentStmt:
		return std::make_unique<AssignStatement>(obj);
		break;
	case CompiledObject::ObjectCode::castStmt:
		return std::make_unique<CastStatement>(obj);
		break;
	case CompiledObject::ObjectCode::incDecStmt:
		return std::make_unique<IncreamentDecreamentStatement>(obj);
		break;
	case CompiledObject::ObjectCode::joinStmt:
		return std::make_unique<JoinStatement>(obj);
		break;
	case CompiledObject::ObjectCode::printStmt:
		return std::make_unique<PrintStatement>(obj);
		break;
	case CompiledObject::ObjectCode::roundStmt:
		return std::make_unique<RoundStatement>(obj);
		break;
	case CompiledObject::ObjectCode::splitStmt:
		return std::make_unique<SplitStatement>(obj);
		break;
	default:
		throw std::runtime_error("Invalid CodeBlock Code");
	}
}

std::shared_ptr<VariableName> Compiler::parseVariableName(const CompiledObject& obj)
{
	if (obj.code() == CompiledObject::ObjectCode::variableExp)
		return std::make_shared<VariableName>(obj);
	else if (obj.code() == CompiledObject::ObjectCode::pronounExp)
		return std::make_shared<Pronoun>(obj);
	else
		throw std::runtime_error("Not a variable name or pronoun exp");
}



std::shared_ptr<IExpression> Compiler::parseCompiledExp(const CompiledObject& obj)
{
	switch (obj.code())
	{
	case CompiledObject::ObjectCode::compareExp:
		return std::make_shared<Comparison>(obj);
		break;
	case CompiledObject::ObjectCode::constantExp:
		return std::make_shared<Constant>(obj);
		break;
	case CompiledObject::ObjectCode::mathExp:
		return std::make_shared<MathExpression>(obj);
		break;
	case CompiledObject::ObjectCode::pronounExp:
	case CompiledObject::ObjectCode::variableExp:
		return parseVariableName(obj);
		break;
	default:
		throw std::runtime_error("Invalid Expression Code");
	}
}
