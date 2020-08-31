#include "Pronoun.h"
#include "InterpeterExceptions.h"

Pronoun::Pronoun(std::shared_ptr<IExpression> index) : VariableName("", index)
{

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