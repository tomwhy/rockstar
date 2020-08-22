#include "Mysterious.h"

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