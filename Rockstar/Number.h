#pragma once
#include "ISimpleVariable.h"
class Number : public ISimpleVariable
{
public:
	Number(double value);
	virtual std::string toString();
	virtual bool canBeIndex();
	virtual bool toBool();

	virtual void increament();
	virtual void decreament();

private:
	double _value;
};

