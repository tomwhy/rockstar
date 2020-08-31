#pragma once

class IRoundable
{
public:
	virtual void ceil() = 0;
	virtual void floor() = 0;
	virtual void round() = 0;
};