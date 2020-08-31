#include "GenericParser/include/Parser.h"
#include "GenericParser/include/ParsingExceptions.h"
#include "RunTime.h"
#include "InterpeterExceptions.h"
#include "Utils.h"
#include "PreProcessor.h"
#include <fstream>
#include <iostream>
#include <algorithm>

#define ARG_COUNT 2
#define ROCKSTAR_DEFS "RockstarDefs.xml"

std::vector<Statement> parseFile(const std::string& filePath);
bool fileExists(const std::string& filePath);


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

std::vector<Statement> parseFile(const std::string& filePath)
{
	Parser parser(ROCKSTAR_DEFS);
	return parser.parse(PreProcessor::readLines(filePath));
}

bool fileExists(const std::string& filePath)
{
	std::fstream file(filePath);
	bool exists = file.is_open();
	file.close();

	return exists;
}