#pragma once
#include "ISimpleVariable.h"

class Mysterious : public ISimpleVariable
{
public:
	Mysterious();
	virtual std::string toString();
	virtual bool canBeIndex();
	virtual bool toBool();
};

