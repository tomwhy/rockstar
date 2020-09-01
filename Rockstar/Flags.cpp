#include "Flags.h"

Flags Flags::operator|(const Flags& rhs) const
{
	return rhs | _value;
}
Flags& Flags::operator|=(const Flags& rhs)
{
	_value = rhs | _value;
	return *this;
}
Flags Flags::operator&(const Flags& rhs) const
{
	return rhs & _value;
}
Flags& Flags::operator&=(const Flags& rhs)
{
	_value = rhs & _value;
	return *this;
}

Flags Flags::operator|(size_t rhs) const
{
	return Flags(_value | rhs);
}
Flags& Flags::operator|=(size_t rhs)
{
	_value = _value | rhs;
	return *this;
}
Flags Flags::operator&(size_t rhs) const
{
	return Flags(_value & rhs);
}
Flags& Flags::operator&=(size_t rhs)
{
	_value = _value & rhs;
	return *this;
}

constexpr Flags::operator size_t() const
{
	return _value;
}