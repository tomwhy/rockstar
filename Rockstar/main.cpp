#include "Interpeter.h"
#include <fstream>
#include <iostream>
#include <algorithm>

#define ARG_COUNT 2


int main(int argc, char** argv)
{
	if (argc != ARG_COUNT)
	{
		std::cerr << "Usage: Rockstar.exe FILE" << std::endl;
		return 1;
	}

	try
	{
		Interpeter interpeter(argv[1]);
		interpeter.run();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}