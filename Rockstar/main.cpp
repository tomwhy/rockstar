#include "GenericParser/include/Parser.h"
#include "GenericParser/include/ParsingExceptions.h"
#include "RunTime.h"
#include "InterpeterException.h"
#include "Utils.h"
#include <fstream>
#include <iostream>
#include <algorithm>

#define ARG_COUNT 2
#define ROCKSTAR_DEFS "RockstarDefs.xml"

std::vector<Statement> parseFile(const std::string& filePath);
bool fileExists(const std::string& filePath);
std::string removeComments(const std::string& line);

int main(int argc, char** argv)
{
	if (argc != ARG_COUNT)
	{
		std::cout << "Usage: Rockstar.exe FILE" << std::endl;
		return 1;
	}

	if (!fileExists(argv[1]))
	{
		std::cout << "Could not open file: " << argv[1] << std::endl;
		return 1;
	}

	std::vector<Statement> lines;
	try
	{
		lines = parseFile(argv[1]);
	}
	catch (const TokenParsingException& e)
	{
		std::cerr << "Error Tokenizing" << std::endl << e.what() << std::endl;
		return 1;
	}
	catch (const StatementParsingException& e)
	{
		std::cerr << "Parsing Error" << std::endl << e.what() << std::endl;
		return 1;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	try
	{
		RunTime runTime(lines);
		runTime.run();
	}
	catch (const InterpeterException& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}

std::string removeComments(const std::string& line)
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

std::vector<Statement> parseFile(const std::string& filePath)
{
	auto readLines = [filePath](std::string& line)
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

		return true;
	};

	Parser parser(ROCKSTAR_DEFS);
	return parser.parse(readLines);
}

bool fileExists(const std::string& filePath)
{
	std::fstream file(filePath);
	bool exists = file.is_open();
	file.close();

	return exists;
}