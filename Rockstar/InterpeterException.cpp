#include "InterpeterException.h"

InterpeterException::InterpeterException(const std::string& msg) : _msg(msg)
{

}
const char* InterpeterException::what() const noexcept
{
	return _msg.c_str();
}
