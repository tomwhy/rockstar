#include <iostream>

#define ARG_COUNT 2

int main(int argc, char** argv)
{
	if (argc != ARG_COUNT)
	{
		std::cout << "Usage Rockstar.exe FILE" << std::endl;
		return 1;
	}

	return 0;
}