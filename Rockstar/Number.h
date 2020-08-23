#pragma once
#include "ISimpleVariable.h"
class Number : public ISimpleVariable
{
public:
	Number(double value);
	virtual std::string toString();
	virtual bool canBeIndex();
	virtual bool toBool();

private:
	double _value;
};

