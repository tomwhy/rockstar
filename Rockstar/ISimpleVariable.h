#pragma once
#include "IVariable.h"

class ISimpleVariable : public IVariable
{
public:
	ISimpleVariable(const std::string& typeName);
	virtual std::shared_ptr<IVariable> getAt(const std::string& index);
	virtual void setAt(const std::string& index, std::shared_ptr<IVariable> value);
};

