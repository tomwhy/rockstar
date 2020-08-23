#pragma once
#include <string>
#include <functional>

class PreProcessor
{
public:
	static std::string removeComments(const std::string& line);
	static std::string removeSingleQuotes(const std::string& line);

	static std::function<bool(std::string&)> readLines(const std::string& filePath);
};

