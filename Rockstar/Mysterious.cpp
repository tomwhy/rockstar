#include "Mysterious.h"
#include "InterpeterExceptions.h"

Mysterious::Mysterious() : ISimpleVariable("Mysterious")
{

}
std::string Mysterious::toString()
{
	return "mysterious";
}
bool Mysterious::canBeIndex()
{
	return false;
}
bool Mysterious::toBool()
{
	return false;
}