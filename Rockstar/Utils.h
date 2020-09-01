#pragma once
#include "IExpression.h"
#include "VariableName.h"
#include "MathExpression.h"
#include "ListArthimeticExpression.h"
#include "Comparison.h"
#include "GenericParser/include/Statement.h"
#include "GenericParser/include/Token.h"
#include <functional>
#include <iterator>

class Utils
{
public:
	static std::shared_ptr<IExpression> createExpression(const Statement& stmt, const std::string& name);
	static std::shared_ptr<MathExpression> createMathExpression(const Statement& stmt, const std::string& name);
	static std::shared_ptr<VariableName> createVariableExpression(const Statement& stmt, const std::string& name);
	static std::shared_ptr<Comparison> createComparisonExpression(const Statement& stmt, const std::string& name);
	static std::shared_ptr<ListArthimeticExpression> createListExpression(const Statement& stmt, const std::string& name, std::shared_ptr<IExpression> left, MathOp op);
	static std::string lower(const std::string& str);
	static std::string repeat(const std::string& str, int times);

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

