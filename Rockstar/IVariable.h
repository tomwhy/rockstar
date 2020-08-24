#pragma once
#include <string>
#include <memory>


class IVariable
{
public:
	IVariable(const std::string& typeName) : _typeName(typeName) {}
	//value functions
	virtual std::string toString() = 0;
	virtual bool toBool() = 0;
	
	//index functions
	virtual std::shared_ptr<IVariable> getAt(const std::string& index) = 0;
	virtual void setAt(const std::string& index, std::shared_ptr<IVariable> value) = 0;

	//meta functions
	virtual bool canBeIndex() = 0;
	std::string type() { return _typeName; }

	//math functions
	virtual void increament() = 0;
	virtual void decreament() = 0;
private:
	std::string _typeName;
};