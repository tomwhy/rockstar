#include "Constant.h"
#include "VariableTypes.h"
#include "InterpeterExceptions.h"
#include "Utils.h"
#include <sstream>

Constant::Constant(const genericparser::Token& value)
{
	if (value.isName("Mysterious"))
	{
		_type = TypeCode::mysterious;
	}
	else if (value.isName("Null"))
	{
		_type = TypeCode::null;
	}
	else if (value.isName("Boolean"))
	{
		_type = TypeCode::boolean;
		_value = value.isName("True") ? "1" : ""; // a non empty string is true else an empty string
	}
	else if (value.isName("Number"))
	{
		_type = TypeCode::number;
		_value = value.value();
	}
	else if (value.isName("String"))
	{
		_type = TypeCode::string;
		_value = value.value().substr(1, value.value().size() - 2);
	}
	else
		throw InterpeterException(value.value() + " is not a constant");
}
Constant::Constant(const CompiledObject& obj)
{
	if (obj.code() != CompiledObject::ObjectCode::constantExp)
		throw std::runtime_error("Not a constant expression");

	_type = obj.at<TypeCode>("type");
	_value = obj.at<std::string>("value");
}


std::shared_ptr<IVariable> Constant::evaluate(Scope& scope) const
{
	switch (_type)
	{
	case TypeCode::mysterious:
		return std::make_shared<Mysterious>();
		break;
	case TypeCode::null:
		return std::make_shared<Null>();
		break;
	case TypeCode::boolean:
		return std::make_shared<Boolean>(!_value.empty());
		break;
	case TypeCode::number:
		return std::make_shared<Number>(std::stold(_value));
		break;
	case TypeCode::string:
		return std::make_shared<String>(_value);
		break;
	default:
		throw std::runtime_error("Invalid type");
	}
}

CompiledObject Constant::serialize() const
{
	//data will be type code and then value
	nlohmann::json json;
	
	json["type"] = _type;
	json["value"] = _value;
	
	return CompiledObject(CompiledObject::ObjectCode::constantExp, json);
}