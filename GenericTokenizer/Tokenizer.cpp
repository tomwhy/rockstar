#include "Tokenizer.h"
#include "TokenParsingException.h"
#include <fstream>
#include <regex>
#include <algorithm>


Tokenizer::Tokenizer(const std::string& xmlPath)
{
	_definitionsDoc.LoadFile(xmlPath.c_str());
	_root = _definitionsDoc.FirstChildElement();
}

std::vector<Token> Tokenizer::tokenizeLine(const std::string& line)
{
	std::vector<Token> tokens;
	int offset = 0;

	while (offset < line.size())
	{
		Token token = getToken(line.substr(offset));
		offset += token.value().size();
		std::smatch match;
		std::string temp = line.substr(offset);
		std::regex_search(temp, match, std::regex(R"(\s*)"));
		offset += match.str().length();
		tokens.push_back(token);
	}

	return tokens;
}

Token Tokenizer::getToken(const std::string& line)
{
	for (tinyxml2::XMLElement* e = _root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		try
		{
			return getToken(line, e);
		}
		catch (const TokenParsingException&)
		{
			continue;
		}
	}

	throw TokenParsingException();
}

Token Tokenizer::getToken(const std::string& line, const tinyxml2::XMLElement* token)
{
	const tinyxml2::XMLAttribute* attr;
	std::string lineCopy(line);

	if ((attr = token->FindAttribute("icase")) != nullptr)
	{
		if (attr->BoolValue())
		{
			std::transform(lineCopy.begin(), lineCopy.end(), lineCopy.begin(), [](char c) {return std::tolower(c); });
		}
	}

	if ((attr = token->FindAttribute("regex")) != nullptr)
	{
		std::smatch match;
		std::regex regex = std::regex(std::string("^") + attr->Value());

		if (std::regex_search(lineCopy, match, regex)) // if there is a regex match
		{
			return Token(token->Name(), match.str());
		}
	}
	for (const tinyxml2::XMLElement* e = token->FirstChildElement(); e != nullptr; e = e->NextSiblingElement())
	{
		try
		{
			Token t = getToken(lineCopy, _root->FirstChildElement(e->Name()));
			t.addName(token->Name());
			return t;
		}
		catch(const TokenParsingException&)
		{
			continue;
		}
	}

	throw TokenParsingException();
}