#pragma once
#include "IVariable.h"
#include <exception>
#include <string>
#include <memory>

class InterpeterException : public std::exception
{
public:
	InterpeterException(const std::string& msg);
	virtual const char* what() const noexcept;
private:
	std::string _msg;
};

class TypeException : public InterpeterException
{
public:
	TypeException(const std::string& msg, std::shared_ptr<IVariable> var);
};