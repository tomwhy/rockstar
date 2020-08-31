#pragma once
#include "IVariable.h"

class ICastable
{
public:
	virtual std::shared_ptr<IVariable> cast(std::shared_ptr<IVariable> arg) = 0;
};