#pragma once
#include <string>
#include <vector>

class Token
{
public:
	Token(const std::string& name, const std::string& value);

	std::string value() const;
	
	void addName(const std::string& name);
	bool isName(const std::string& name);

private:
	std::vector<std::string> _names;
	std::string _value;
};