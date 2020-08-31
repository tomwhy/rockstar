#include "InterpeterExceptions.h"

InterpeterException::InterpeterException(const std::string& msg) : _msg(msg)
{

}
const char* InterpeterException::what() const noexcept
{
	return _msg.c_str();
}

TypeException::TypeException(const std::string& msg, std::shared_ptr<IVariable> var) : InterpeterException(msg + var->_typeName)
{

}