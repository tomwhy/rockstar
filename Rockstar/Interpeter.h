#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "RunTime.h"
#include "GenericParser/include/Parser.h"


class Interpeter
{
public:
	Interpeter(const std::string& filePath);

	void run();
private:
	std::ifstream _file;
	Parser _parser;
	RunTime _runtime;
};

