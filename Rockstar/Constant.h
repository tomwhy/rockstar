#pragma once
#include "IExpression.h"
#include "GenericParser/include/Token.h"




class Constant : public IExpression
{
public:
	enum class TypeCode { mysterious, null, boolean, number, string };

	Constant(const genericparser::Token& value);
	Constant(const CompiledObject& obj);
	virtual std::shared_ptr<IVariable> evaluate(Scope& scope) const;
	virtual CompiledObject serialize() const;
private:
	TypeCode _type;
	std::string _value;
};

