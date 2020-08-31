#pragma once

class IIncreameantable
{
public:
	virtual void increament(size_t count) = 0;
	virtual void decreament(size_t count) = 0;
};