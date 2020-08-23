#pragma once
#include <exception>

class Exception : public std::exception
{
public:
	Exception(const std::string& msg) : _msg(msg) {};
	const char* what() const noexcept { return _msg.c_str(); }
private:
	std::string _msg;
};

class TokenParsingException : public Exception
{
public:
	TokenParsingException(const std::string& msg) : Exception(msg) {};

};

class StatementParsingException : public Exception
{
public:
	StatementParsingException(const std::string& msg) : Exception(msg) {};
};