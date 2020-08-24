#pragma once
#include "ISimpleVariable.h"

class Boolean : public ISimpleVariable
{
public:
	Boolean(bool value);
	virtual std::string toString();
	virtual bool toBool();
	virtual bool canBeIndex();

	virtual void increament();
	virtual void decreament();
	

private:
	bool _value;
};

