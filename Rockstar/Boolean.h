#pragma once
#include "ISimpleVariable.h"
#include "IIncreametable.h"
#include "MathInterfaces.h"

class Boolean : public ISimpleVariable, public IIncreameantable
{
public:
	Boolean(bool value);
	virtual std::string toString();
	virtual bool toBool();
	virtual bool canBeIndex();
	
	virtual void increament(size_t count);
	virtual void decreament(size_t count);

private:
	bool _value;
};

