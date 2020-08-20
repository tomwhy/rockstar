#pragma once
#include "Token.h"
#include "tinyxml2/tinyxml2.h"
#include <regex>


class Tokenizer
{
public:
	Tokenizer(tinyxml2::XMLElement* tokenDefs, tinyxml2::XMLElement* defineTags);

	std::vector<Token> tokenizeLine(const std::string& line);
	
	static tinyxml2::XMLElement* findTag(const std::string& name, std::vector<tinyxml2::XMLElement*> defs);

private:
	Token getToken(const std::string& line);
	Token getToken(const std::string& line, const tinyxml2::XMLElement* token);

	std::vector<std::regex> getTokenRegexes(const tinyxml2::XMLElement* token);
	bool checkInvalid(const std::string& str, const tinyxml2::XMLElement* token);


	tinyxml2::XMLElement* _tokenDefs;
	tinyxml2::XMLElement* _definesTags;
};