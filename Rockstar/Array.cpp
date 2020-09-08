#include "Array.h"
#include "Utils.h"
#include "Mysterious.h"
#include "Null.h"
#include "Number.h"
#include "InterpeterExceptions.h"

Array::Array(const std::string& index, std::shared_ptr<IVariable> value) : _size(), _data(), IVariable("Array")
{
	_data[index] = value;
	updateSize(index);
}

bool Array::canBeIndex()
{
	return true;
}

bool Array::toBool()
{
	return (bool)_size;
}

std::string Array::toString()
{
	return std::to_string(_size);
}
std::shared_ptr<IVariable> Array::getAt(const std::string& index)
{
	if (_data.find(index) == _data.end())
		return std::make_shared<Mysterious>();
	return _data.at(index);
}
void Array::updateSize(const std::string& index)
{
	if (Utils::all<std::string::const_iterator, char>(index.begin(), index.end(), [](char c) {return std::isdigit(c); }))
	{
		int intIndex = std::stoi(index);
		if (_size - 1 < intIndex)
		{
			_size = intIndex + 1;
		}
	}
}
void Array::setAt(const std::string& index, std::shared_ptr<IVariable> value)
{
	_data[index] = value;
	updateSize(index);
}

std::shared_ptr<String> Array::join(std::shared_ptr<IVariable> delim)
{
	std::string res;
	std::string delimStr = delim == nullptr ? "" : delim->toString();

	for (int i = 0; i < _size; i++)
	{
		std::shared_ptr<IVariable> valueAtIndex = _data[std::to_string(i)];
		if (std::dynamic_pointer_cast<Mysterious>(valueAtIndex) == nullptr && std::dynamic_pointer_cast<Null>(valueAtIndex) == nullptr)
		{ //if the value is not of type null or mysterious
			res += valueAtIndex->toString();
			if (i < _size - 1)
			{
				res += delimStr;
			}
		}
	}

	return std::make_shared<String>(res);
}

bool Array::equal(std::shared_ptr<IVariable> other)
{
	return Number(_size).equal(other);
}

bool Array::less(std::shared_ptr<IVariable> other)
{
	return Number(_size).less(other);
}
