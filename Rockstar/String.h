#pragma once
#include "IVariable.h"
class String : public IVariable
{
public:
	String(const std::string& value);
	virtual std::string toString();
	virtual bool toBool();
	virtual std::shared_ptr<IVariable> getAt(const std::string& index);
	virtual void setAt(const std::string& index, std::shared_ptr<IVariable> value);
	virtual bool canBeIndex();

	virtual void increament();
	virtual void decreament();

private:
	std::string _value;
};

