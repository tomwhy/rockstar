#include "CompiledObject.h"
#include "json.hpp"
#include <numeric>
#include <stdexcept>

CompiledObject::CompiledObject(ObjectCode code, const nlohmann::json& properties) :
	_properties(properties)
{
	_properties["code"] = code;
}
CompiledObject::CompiledObject(std::vector<std::uint8_t> serializedBuffer)
{
	_properties = nlohmann::json::from_msgpack(serializedBuffer);
}

std::vector<std::uint8_t> CompiledObject::getCompiledObject() const
{
	std::vector<std::uint8_t> res = nlohmann::json::to_msgpack(_properties);

	size_t size = res.size();

	res.insert(res.begin(), (std::uint8_t*)&size, (std::uint8_t*)&size + sizeof(size_t));
	
	return res;
}
CompiledObject::ObjectCode CompiledObject::code() const
{
	return _properties.at("code").get<ObjectCode>();
}
bool CompiledObject::contains(const char* idx) const
{
	return _properties.contains(idx);
}
void CompiledObject::setCode(ObjectCode code)
{
	_properties["code"] = code;
}
size_t CompiledObject::size() const
{
	return nlohmann::json::to_msgpack(_properties).size();
}
