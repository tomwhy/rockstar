#pragma once
#include <string>
#include <vector>
#include "RunTime.h"

class Interpeter
{
public:
	Interpeter(const std::string& filePath);

	void run();
private:
	static std::vector<Statement> parseFile(const std::string& filePath);

	
	RunTime _runtime;
};

