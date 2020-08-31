#pragma once
#include "IVariable.h"

class ISplitable
{
public:
	virtual std::shared_ptr<IVariable> split(std::shared_ptr<IVariable> arg) = 0;
};