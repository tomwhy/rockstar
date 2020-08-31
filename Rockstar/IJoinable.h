#pragma once
#include "String.h"

class IJoinable
{
public:
	virtual std::shared_ptr<String> join(std::shared_ptr<IVariable> delim) = 0;
};