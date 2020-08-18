#pragma once
#include "Token.h"
#include "tinyxml2/tinyxml2.h"


class Tokenizer
{
public:
	Tokenizer(const std::string& xmlPath);

	std::vector<Token> tokenizeLine(const std::string& line);

private:
	Token getToken(const std::string& line);
	Token getToken(const std::string& line, const tinyxml2::XMLElement* token);

	tinyxml2::XMLDocument _definitionsDoc;
	tinyxml2::XMLElement* _root;

};