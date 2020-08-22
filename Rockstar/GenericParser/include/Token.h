#pragma once
#include <string>
#include <vector>
#include <map>

class Token
{
public:
	Token(const std::string& name);
	Token(const std::string& name, const std::map<size_t, std::string>& groups);
	Token();

	std::string value() const;
	std::string group(int group) const;
	std::map<size_t, std::string> groups() const;

	void addName(const std::string& name);
	void addName(const std::vector<std::string>& names);
	bool isName(const std::string& name) const;
	const std::vector<std::string> getNames() const;
	friend bool operator<(const Token& left, const Token& right);

private:
	std::vector<std::string> _names;
	std::map<size_t, std::string> _groups;
};