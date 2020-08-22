#pragma once
#include <string>
#include <memory>

class IVariable
{
public:
	IVariable(const std::string& typeName) : _typeName(typeName) {}
	virtual std::string toString() = 0;

	virtual std::shared_ptr<IVariable> getAt(const std::string& index) = 0;
	virtual void setAt(const std::string& index, std::shared_ptr<IVariable> value) = 0;

	virtual bool canBeIndex() = 0;
	std::string type() { return _typeName; }

private:
	std::string _typeName;
};