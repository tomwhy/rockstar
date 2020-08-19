#pragma once
#include <exception>

class TokenParsingException : public std::exception
{

};

class StatementParsingException : public std::exception
{

};