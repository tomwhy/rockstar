#pragma once
#include "IExpression.h"
#include "VariableName.h"


class Pronoun : public VariableName
{
public:
	Pronoun(std::shared_ptr<IExpression> index = {});
	Pronoun(const CompiledObject& obj);
	virtual std::shared_ptr<IVariable> evaluate(Scope& scope) const;
	virtual CompiledObject serialize() const;

	virtual std::string name(Scope& scope) const;
private:
	static CompiledObject preprocessObj(const CompiledObject& obj);

	std::shared_ptr<IExpression> _index;
};

