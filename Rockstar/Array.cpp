#include "Array.h"
#include "Utils.h"
#include "Mysterious.h"

Array::Array(const std::string& index, std::shared_ptr<IVariable> value) : _size(), _data(), IVariable("Array")
{
	_data[index] = value;
	updateSize(index);
}

bool Array::canBeIndex()
{
	return false;
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
	if (Utils::all<std::string::const_iterator, char>(index.begin(), index.end(), std::isdigit))
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