#pragma once
#include "Statement.h"
#include "Tokenizer.h"


class Parser
{
public:
	Parser(const std::string& xmlDefenitions);
	~Parser();

	std::vector<Statement> parse(const std::string& filePath);

private:
	Statement parseLine(const std::vector<Token>& tokens);
	std::map<Token, std::string> parseLine(const std::vector<Token>& tokens, const tinyxml2::XMLElement* sequence);
	std::map<Token, std::string> parseOr(const std::vector<Token>& tokens, const tinyxml2::XMLElement* orElem);


	tinyxml2::XMLDocument _definitionsDoc;
	tinyxml2::XMLElement* _statementDefs;
	Tokenizer* _tokenizer;
};

