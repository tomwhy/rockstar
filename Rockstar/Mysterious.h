#pragma once
#include "ISimpleVariable.h"

class Mysterious : public ISimpleVariable
{
public:
	virtual std::string toString();
	virtual bool canBeIndex();
};

