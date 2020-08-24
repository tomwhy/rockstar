#pragma once
#include "ISimpleVariable.h"

class Boolean : public ISimpleVariable
{
public:
	Boolean(bool value);
	virtual std::string toString();
	virtual bool toBool();
	virtual bool canBeIndex();
	

private:
	bool _value;
};

