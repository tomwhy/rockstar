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
	std::regex stringLiteralRegexBoundry(R"(^[^\\"]*(?!\\)("))");


	size_t offset = 0;
	while (offset < res.size())
	{
		size_t saysPos = std::string::npos;
		std::smatch match;
		std::string subString = res.substr(offset);

		saysPos = res.find("says", offset);

		if (std::regex_search(subString, match, stringLiteralRegexBoundry))
		{
			size_t stringOffset = match.position(1) + offset;
			if (saysPos != std::string::npos && saysPos < stringOffset)
				break;
			
			res.erase(std::remove(res.begin() + offset, res.begin() + stringOffset, '\''), res.begin() + stringOffset);
			subString = res.substr(stringOffset+1);
			if (std::regex_search(subString, match, stringLiteralRegexBoundry))
			{
				offset = stringOffset + match.position(1) + 2;
				if (res[offset] == ',') //insert a space between an end of string literal and a comma (because \b is \w\W|\W\w|^\w|\w$ and both " and , are \W)
					res.insert(res.begin() + offset, ' '); //a temporary solution until a better one is found
				offset++;
			}
			else
			{
				throw std::exception(("Expected end of string literal. line: " + line).c_str());
			}
		}
		else
		{
			if (saysPos == std::string::npos)
			{
				res.erase(std::remove(res.begin() + offset, res.end(), '\''), res.end());
			}
			else
			{
				res.erase(std::remove(res.begin() + offset, res.begin() + saysPos, '\''), res.begin() + saysPos);
			}

			break;
		}
	}

	return res;
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