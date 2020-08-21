#pragma once
#include "IExpression.h"
#include "GenericParser/include/Token.h"
#include <functional>
#include <iterator>

class Utils
{
public:
	static std::shared_ptr<IExpression> createExpression(const Token& token);
	static std::string lower(const std::string& str);
	
	template <class Iter, class T>
	static bool all(const Iter& begin, const Iter& end, std::function<bool(T)> pred)
	{
		for (Iter it = begin; it != end; ++it)
		{
			if (!pred(*it))
				return false;
		}

		return true;
	}
};

