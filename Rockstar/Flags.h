#pragma once
#include "json.hpp"

class Flags
{
public:
	constexpr Flags(size_t flags) : _value(flags) {};

	Flags operator|(const Flags& rhs) const;
	Flags& operator|=(const Flags& rhs);
	Flags operator&(const Flags& rhs) const;
	Flags& operator&=(const Flags& rhs);

	Flags operator|(size_t rhs) const;
	Flags& operator|=(size_t rhs);
	Flags operator&(size_t rhs) const;
	Flags& operator&=(size_t rhs);

	constexpr operator size_t() const;

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Flags, _value);

private:
	size_t _value;
};
