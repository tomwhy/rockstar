#pragma once
#include "IVariable.h"
class Number : public IVariable
{
public:
	Number(double value);
	virtual std::string toString();
private:
	double _value;
};

