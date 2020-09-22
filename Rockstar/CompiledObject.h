#pragma once
#include <vector>
#include "json.hpp"

class CompiledObject
{
private:
	nlohmann::json _properties;

public:

	enum class ObjectCode {compareExp, constantExp, mathExp, pronounExp, variableExp, assignmentStmt, castStmt, joinStmt, splitStmt, incDecStmt, printStmt, roundStmt};

	CompiledObject(ObjectCode code, const nlohmann::json& properties);
	CompiledObject(std::vector<std::uint8_t> serializedBuffer);
	CompiledObject() = default;

	std::vector<std::uint8_t> getCompiledObject() const;
	ObjectCode code() const;
	void setCode(ObjectCode code);
	size_t size() const;
	bool contains(const char* idx) const;
	
	
	template <class T>
	T at(const char* idx) const
	{
		return _properties[idx].get<T>();
	}

	NLOHMANN_DEFINE_TYPE_INTRUSIVE(CompiledObject, _properties);
};

