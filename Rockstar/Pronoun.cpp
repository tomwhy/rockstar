#include "Pronoun.h"

std::shared_ptr<IVariable> Pronoun::evaluate(Scope& scope) const
{
	return scope.getLast();
}