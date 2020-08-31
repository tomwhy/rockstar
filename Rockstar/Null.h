#pragma once
#include "ISimpleVariable.h"
#include "MathInterfaces.h"

class Null : public ISimpleVariable, public IMathable
{
public:
	Null();
	virtual std::string toString();
	virtual bool canBeIndex();
	virtual bool toBool();

	virtual std::shared_ptr<IVariable> add(std::shared_ptr<IVariable> other);
	virtual std::shared_ptr<IVariable> subtract(std::shared_ptr<IVariable> other);
	virtual std::shared_ptr<IVariable> multiply(std::shared_ptr<IVariable> other);
	virtual std::shared_ptr<IVariable> divide(std::shared_ptr<IVariable> other);

};

