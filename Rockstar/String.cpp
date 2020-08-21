#include "String.h"
#include "Mysterious.h"
#include "InterpeterException.h"
#include "Utils.h"

String::String(const std::string& value) : _value(value)
{

}

std::string String::toString()
{
	return _value;
}

bool String::canBeIndex()
{
	return true;
}

std::shared_ptr<IVariable> String::getAt(const std::string& index)
{
	if (Utils::all<std::string::const_iterator, char>(index.begin(), index.end(), std::isdigit))
	{
		int intIndex = std::stoi(index);
		if (intIndex >= _value.size() || intIndex < 0)
			return std::make_shared<Mysterious>();

		std::string res;
		res.push_back(_value.at(intIndex));

		return std::make_shared<String>(res);
	}

	return std::make_shared<Mysterious>();
}
void String::setAt(const std::string& index, std::shared_ptr<IVariable> value)
{
	throw InterpeterException("String is read-only");
}