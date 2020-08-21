#include "Pronoun.h"
#include "InterpeterException.h"

Pronoun::Pronoun(std::shared_ptr<IExpression> index) : _index(index)
{

}

std::shared_ptr<IVariable> Pronoun::evaluate(Scope& scope) const
{
	if (_index == nullptr)
		return scope.getLast();
	else
	{
		std::shared_ptr<IVariable> indexVar = _index->evaluate(scope);
		if (!indexVar->canBeIndex())
			throw InterpeterException(indexVar->toString() + " cannot be index");
		return scope.getLast()->getAt(indexVar->toString());
	}
}