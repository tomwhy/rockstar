#include "Null.h"
#include "InterpeterException.h"

Null::Null() : ISimpleVariable("Null")
{

}

std::string Null::toString()
{
	return "null";
}

bool Null::canBeIndex()
{
	return false;
}
bool Null::toBool()
{
	return false;
}
