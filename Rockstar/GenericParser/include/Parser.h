#pragma once
#include "Statement.h"
#include "Tokenizer.h"
#include <functional>

typedef std::vector<std::pair<Token, std::string>> Possibility;

class Parser
{
public:
	Parser(const std::string& xmlDefenitions);
	~Parser();

	std::vector<Statement> parse(const std::string& filePath);
	std::vector<Statement> parse(const std::function<bool(std::string& line)>& lineFunc);

private:
	static std::function<size_t(const Possibility&)> _possibilityLength;
	
	static std::regex createRegex(const Possibility& p);
	Statement parseLine(const std::string& line);
	std::vector<Possibility> parseTag(const std::string& line, const tinyxml2::XMLElement* tag, bool defineTag = false);

	tinyxml2::XMLDocument _definitionsDoc;
	tinyxml2::XMLElement* _statementDefs;
	tinyxml2::XMLElement* _defineTags;
	Tokenizer* _tokenizer;
};

