#include "GenericParser/include/Parser.h"
#include "GenericParser/include/ParsingExceptions.h"
#include <fstream>
#include <iostream>

#define ARG_COUNT 2
#define ROCKSTAR_DEFS "RockstarDefs.xml"

std::vector<Statement> parseFile(const std::string& filePath);
bool fileExists(const std::string& filePath);
int executeFile(const std::string& filePath);

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
	catch (const TokenParsingException&)
	{
		std::cerr << "Error Tokenizing" << std::endl;
		return 1;
	}
	catch (const StatementParsingException&)
	{
		std::cerr << "Unknow Statment" << std::endl;
		return 1;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}


	return 0;
}

std::vector<Statement> parseFile(const std::string& filePath)
{
	Parser parser(ROCKSTAR_DEFS);
	return parser.parse(filePath);
	
}

bool fileExists(const std::string& filePath)
{
	std::fstream file(filePath);
	bool exists = file.is_open();
	file.close();

	return exists;
}