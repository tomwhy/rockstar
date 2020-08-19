#pragma once
#include "Token.h"
#include <string>
#include <map>


class Statement
{
public:
	Statement(const std::string& name, const std::map<std::string, Token>& tokens);
	Statement(const std::string& name);

	void addToken(const std::string& tokenName, const Token& token);

	const std::string name() const;
	const Token getToken(const std::string& tokenName) const;

private:
	std::string _name;
	std::map<std::string, Token> _tokens;
};

