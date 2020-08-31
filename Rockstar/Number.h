#pragma once
#include "ISimpleVariable.h"
#include "ICastable.h"
#include "IIncreametable.h"
#include "MathInterfaces.h"
#include "IRoundable.h"

class Number : public ISimpleVariable, public ICastable, public IIncreameantable, public IMathable, public IRoundable
{
public:
	Number(long double value);
	virtual std::string toString();
	virtual bool canBeIndex();
	virtual bool toBool();

	//modifiers
	virtual std::shared_ptr<IVariable> cast(std::shared_ptr<IVariable> arg);

	//increament/decreament
	virtual void increament(size_t count);
	virtual void decreament(size_t count);

	//math
	virtual std::shared_ptr<IVariable> add(std::shared_ptr<IVariable> other);
	virtual std::shared_ptr<IVariable> subtract(std::shared_ptr<IVariable> other);
	virtual std::shared_ptr<IVariable> multiply(std::shared_ptr<IVariable> other);
	virtual std::shared_ptr<IVariable> divide(std::shared_ptr<IVariable> other);

	//rounding
	virtual void ceil();
	virtual void floor();
	virtual void round();

private:
	long double _value;
};

