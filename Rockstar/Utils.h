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
	static std::shared_ptr<IExpression> createExpression(const genericparser::Statement& stmt, const std::string& name);
	static std::shared_ptr<MathExpression> createMathExpression(const genericparser::Statement& stmt, const std::string& name);
	static std::shared_ptr<VariableName> createVariableExpression(const genericparser::Statement& stmt, const std::string& name);
	static std::shared_ptr<Comparison> createComparisonExpression(const genericparser::Statement& stmt, const std::string& name);
	static std::shared_ptr<ListArthimeticExpression> createListExpression(const genericparser::Statement& stmt, const std::string& name, std::shared_ptr<IExpression> left, MathOp op);
	static genericparser::Statement parseExpression(const std::vector<genericparser::Token>& line, const std::string& name);
	static std::string lower(const std::string& str);
	static std::string repeat(const std::string& str, int times);
	static std::string getDefsPath();

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

	template <typename Iter>
	static std::vector<char> serializeType(Iter begin, Iter end)
	{
		return std::vector<char>(begin, end);
	}

	template <typename T>
	static std::vector<char> serializeType(T value)
	{
		return serializeType((char*)&value, (char*)&value + sizeof(T));
	}
};

