#pragma once
#include "Token.h"
#include "tinyxml2/tinyxml2.h"
#include <regex>


class Tokenizer
{
public:
	Tokenizer(tinyxml2::XMLElement* tokenDefs);

	tinyxml2::XMLElement* findTag(const std::string& name, const char* parent);
	std::vector<Token> TokenizeLine(const std::string& line);

private:
	Token getToken(const std::string& line, const tinyxml2::XMLElement* token);
	std::vector<std::regex> getTokenRegexes(const tinyxml2::XMLElement* token);
	bool checkInvalid(const std::string& str, const tinyxml2::XMLElement* token);



	tinyxml2::XMLElement* _tokenDefs;
};