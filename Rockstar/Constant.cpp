#include "Constant.h"
#include "VariableTypes.h"
#include "InterpeterException.h"

Constant::Constant(const Token& value) : _value(value)
{

}
const IVariable* Constant::evaluate(Scope& scope) const
{
	if (_value.isName("Mysterious"))
		return new Mysterious();
	else if (_value.isName("Null"))
		return new Null();
	else if (_value.isName("Boolean"))
		return new Boolean(_value.isName("True"));
	else if (_value.isName("Number"))
		return new Number(std::stod(_value.value()));
	else if (_value.isName("String"))
		return new String(_value.value().substr(1, _value.value().size() - 1));
	else
		throw InterpeterException(_value.value() + " is not a constant");
}
