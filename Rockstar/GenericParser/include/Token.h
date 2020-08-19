#pragma once
#include <string>
#include <vector>

class Token
{
public:
	Token(const std::string& name, const std::string& value);
	Token();

	std::string value() const;
	
	void addName(const std::string& name);
	void addName(const std::vector<std::string>& names);
	bool isName(const std::string& name);
	friend bool operator<(const Token& left, const Token& right);

private:
	std::vector<std::string> _names;
	std::string _value;
};