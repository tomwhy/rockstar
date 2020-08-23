#pragma once
#include "Statement.h"
#include "Tokenizer.h"
#include <functional>


class Parser
{
public:
	Parser(const std::string& xmlDefenitions);
	~Parser();

	std::vector<Statement> parse(const std::string& filePath);
	std::vector<Statement> parse(const std::function<bool(std::string& line)>& lineFunc);

private:
	Statement parseLine(const std::string& line);
	std::vector<std::pair<Token, std::string>> parseSequence(const std::string& line, const tinyxml2::XMLElement* sequence);
	std::vector<std::pair<Token, std::string>> parseOr(const std::string& line, const tinyxml2::XMLElement* orElem);
	std::vector<std::pair<Token, std::string>> parseToken(const std::string& line, const tinyxml2::XMLElement* elem);

	tinyxml2::XMLDocument _definitionsDoc;
	tinyxml2::XMLElement* _statementDefs;
	tinyxml2::XMLElement* _defineTags;
	Tokenizer* _tokenizer;
};

