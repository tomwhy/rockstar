#include "Pronoun.h"
#include "InterpeterExceptions.h"
#include "Compiler.h"

Pronoun::Pronoun(std::shared_ptr<IExpression> index) : VariableName("", index)
{

}
Pronoun::Pronoun(const CompiledObject& obj) : VariableName(preprocessObj(obj))
{

}

CompiledObject Pronoun::preprocessObj(const CompiledObject& obj)
{
	CompiledObject res = obj;
	if (res.code() != CompiledObject::ObjectCode::pronounExp)
		throw std::runtime_error("Not a pronoun expression");

	res.setCode(CompiledObject::ObjectCode::variableExp);
	return res;
}


std::string Pronoun::name(Scope& scope) const
{
	return scope.getLastName();
}

std::shared_ptr<IVariable> Pronoun::evaluate(Scope& scope) const
{
	if (_index == nullptr)
		return scope.getLast();
	else
	{
		return scope.getLast()->getAt(index(scope));
	}
}

CompiledObject Pronoun::serialize() const
{
	CompiledObject res = VariableName::serialize();
	res.setCode(CompiledObject::ObjectCode::pronounExp);
	return res;
}