#pragma once
#include <string>

class IVariable
{
public:
	virtual std::string toString() = 0;
};