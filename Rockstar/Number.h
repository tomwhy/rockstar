#pragma once
#include "ISimpleVariable.h"
class Number : public ISimpleVariable
{
public:
	Number(long double value);
	virtual std::string toString();
	virtual bool canBeIndex();
	virtual bool toBool();

private:
	long double _value;
};

