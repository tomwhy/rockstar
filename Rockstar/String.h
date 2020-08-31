#pragma once
#include "IVariable.h"
#include "ICastable.h"
#include "MathInterfaces.h"
#include "ISplitable.h"

class String : public IVariable, public ICastable, public IMultiplyable, public ISplitable
{
public:
	String(const std::string& value);
	virtual std::string toString();
	virtual bool toBool();
	virtual std::shared_ptr<IVariable> getAt(const std::string& index);
	virtual void setAt(const std::string& index, std::shared_ptr<IVariable> value);
	virtual bool canBeIndex();

	virtual std::shared_ptr<IVariable> cast(std::shared_ptr<IVariable> arg);
	virtual std::shared_ptr<IVariable> split(std::shared_ptr<IVariable> arg);
	virtual std::shared_ptr<IVariable> multiply(std::shared_ptr<IVariable> other);

private:
	std::string _value;
};

