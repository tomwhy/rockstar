#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "RunTime.h"
#include "Compiler.h"


class Interpeter
{
public:
	Interpeter(const std::string& filePath);

	void run();
private:
	Compiler _compiler;
	RunTime _runtime;
};

