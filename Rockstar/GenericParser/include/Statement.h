#pragma once
#include "Token.h"
#include <string>
#include <map>

namespace genericparser
{

	class Statement
	{
	public:
		Statement(const std::string& name, const std::map<std::string, std::vector<Token>>& tokens);
		Statement(const std::string& name);

		void addToken(const std::string& tokenName, const Token& token);

		const std::string name() const;
		const Token getToken(const std::string& tokenName, size_t index = 0) const;
		const std::vector<Token> getTokens(const std::string& tokenName) const;
		const bool hasToken(const std::string& tokenName) const;
		bool contains(const std::string& tokenPrefix) const;

	private:
		std::string _name;
		std::map<std::string, std::vector<Token>> _tokens;
	};

}