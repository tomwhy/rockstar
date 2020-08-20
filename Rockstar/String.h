#pragma once
#include "IVariable.h"
class String : public IVariable
{
public:
	String(const std::string& value);
	virtual std::string toString();
private:
	std::string _value;
};

