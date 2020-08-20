#pragma once
#include <exception>
#include <string>

class InterpeterException : public std::exception
{
public:
	InterpeterException(const std::string& msg);
	virtual const char* what() const noexcept;
private:
	std::string _msg;
};