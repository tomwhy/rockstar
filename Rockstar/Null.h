#pragma once
#include "ISimpleVariable.h"

class Null : public ISimpleVariable
{
public:
	Null();
	virtual std::string toString();
	virtual bool canBeIndex();
	virtual bool toBool();

};

