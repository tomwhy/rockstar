#pragma once

class IVariable;

class IOrderable
{
public:
	virtual bool less(std::shared_ptr<IVariable> other) = 0;

};

class IEqualable
{
public:
	virtual bool equal(std::shared_ptr<IVariable> other) = 0;
};