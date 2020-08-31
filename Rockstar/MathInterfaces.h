#pragma once
#include "IVariable.h"


class ISubtractable
{
public:
	virtual std::shared_ptr<IVariable> subtract(std::shared_ptr<IVariable> other) = 0;
};

class IMultiplyable
{
public:
	virtual std::shared_ptr<IVariable> multiply(std::shared_ptr<IVariable> other) = 0;
};

class IDivieable
{
public:
	virtual std::shared_ptr<IVariable> divide(std::shared_ptr<IVariable> other) = 0;
};

class IMathable : public ISubtractable, public IMultiplyable, public IDivieable
{

};