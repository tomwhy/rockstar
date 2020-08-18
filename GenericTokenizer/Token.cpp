#include "Token.h"

Token::Token(const std::string& name, const std::string& value) : _names({name}), _value(value)
{

}

void Token::addName(const std::string& name)
{
	_names.push_back(name);
}
bool Token::isName(const std::string& name)
{
	return std::find(_names.begin(), _names.end(), name) != _names.end();
}

std::string Token::value() const
{
	return _value;
}
