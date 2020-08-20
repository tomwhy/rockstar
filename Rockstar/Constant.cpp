#include "Constant.h"
#include "VariableTypes.h"
#include "InterpeterException.h"

Constant::Constant(const Token& value) : _value(value)
{

}
std::shared_ptr<IVariable> Constant::evaluate(Scope& scope) const
{
	if (_value.isName("Mysterious"))
		return std::make_shared<Mysterious>();
	else if (_value.isName("Null"))
		return std::make_shared<Null>();
	else if (_value.isName("Boolean"))
		return std::make_shared<Boolean>(_value.isName("True"));
	else if (_value.isName("Number"))
		return std::make_shared<Number>(std::stod(_value.value()));
	else if (_value.isName("String"))
		return std::make_shared<String>(_value.value().substr(1, _value.value().size() - 2)); //remove the surrounding "
	else
		throw InterpeterException(_value.value() + " is not a constant");
}
