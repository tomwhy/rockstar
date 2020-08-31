#pragma once
#include "IVariable.h"
#include "IJoinable.h"
#include <map>

class Array : public IVariable, public IJoinable
{
public:
	Array(const std::string& index, std::shared_ptr<IVariable> value);

	virtual std::string toString();
	virtual bool toBool();
	virtual std::shared_ptr<IVariable> getAt(const std::string& index);
	virtual void setAt(const std::string& index, std::shared_ptr<IVariable> value);
	virtual bool canBeIndex();

	virtual std::shared_ptr<String> join(std::shared_ptr<IVariable> delim);

private:
	void updateSize(const std::string& index);
	std::map<std::string, std::shared_ptr<IVariable>> _data;
	int _size;
};

