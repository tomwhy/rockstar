#pragma once
#include "ISimpleVariable.h"

class Null : public ISimpleVariable
{
public:
	virtual std::string toString();
	virtual bool canBeIndex();
};

