#pragma once
#include "ISimpleVariable.h"
#include "MathInterfaces.h"

class Mysterious : public ISimpleVariable
{
public:
	Mysterious();
	virtual std::string toString();
	virtual bool canBeIndex();
	virtual bool toBool();
};

