#include "PreProcessor.h"
#include <regex>
#include <fstream>

std::string PreProcessor::removeComments(const std::string& line)
{
	static bool inComment = false;
	std::string res(line);
	std::regex commentRegex(R"(\(.*?\))"); //remove in line comments


	if (!inComment)
	{
		res = std::regex_replace(res, commentRegex, "");

		size_t commentStart = res.find('(');
		if (inComment = commentStart != std::string::npos)
		{
			return res.substr(0, commentStart);
		}
	}
	else
	{
		size_t commentEnd = res.find(')');
		if (inComment = commentEnd == std::string::npos)
		{
			return "";
		}
		else
		{
			res = res.substr(commentEnd + 1);

			res = std::regex_replace(res, commentRegex, "");

			size_t commentStart = res.find('(');
			if (inComment = commentStart != std::string::npos)
			{
				return res.substr(0, commentStart);
			}
		}
	}

	return res;
}
std::string PreProcessor::removeSingleQuotes(const std::string& line)
{
	std::regex shortcutRegex(R"('s\W+)");
	std::string res = std::regex_replace(line, shortcutRegex, " is ");

	return std::regex_replace(res, std::regex(R"(')"), ""); //remove all other signle quotes
}

std::function<bool(std::string&)> PreProcessor::readLines(const std::string& filePath)
{
	return  [filePath](std::string& line)
	{
		static std::fstream file(filePath, std::fstream::in);
		std::regex emptyLineRegex(R"(^\s*$)");


		if (!std::getline(file, line))
		{
			file.close();
			return false;
		}

		line = removeComments(line);
		while (std::regex_match(line, emptyLineRegex))
		{
			if (!std::getline(file, line))
			{
				file.close();
				return false;
			}

			line = removeComments(line);
		}

		line = removeSingleQuotes(line);

		return true;
	};
}