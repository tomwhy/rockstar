#pragma once
#include "Statement.h"
#include "Tokenizer.h"
#include "PossibilityIterator.h"
#include <functional>
#include <memory>


class Parser
{
public:
	Parser(const std::string& xmlDefenitions);
	~Parser();

	std::vector<Statement> parse(const std::string& filePath);
	std::vector<Statement> parse(const std::function<bool(std::string& line)>& lineFunc);

private:
	static std::regex createRegex(const Possibility& p);
	Statement parseLine(const std::string& line);

	tinyxml2::XMLDocument _definitionsDoc;
	tinyxml2::XMLElement* _statementDefs;
	tinyxml2::XMLElement* _defineTags;
	Tokenizer* _tokenizer;
};

