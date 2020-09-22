#pragma once
#include "Token.h"
#include "tinyxml2/tinyxml2.h"
#include <vector>
#include <stack>

namespace genericparser
{
	struct Possibility
	{
		std::vector<std::pair<Token, std::string>> tokens;

		size_t size() const;
	};
}
