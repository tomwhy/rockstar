#pragma once
#include "IVariable.h"

class Boolean : public IVariable
{
public:
	Boolean(bool value);
	virtual std::string toString();

private:
	bool _value;
};

