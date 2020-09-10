#include "Interpeter.h"
#include "PreProcessor.h"
#include "GenericParser/include/Parser.h"
#include "Utils.h"


Interpeter::Interpeter(const std::string& filePath) : _runtime(parseFile(filePath))
{

}

std::vector<Statement> Interpeter::parseFile(const std::string& filePath)
{
	Parser parser(Utils::getDefsPath());
	return parser.parse(PreProcessor::readLines(filePath));
}

void Interpeter::run()
{
	_runtime.run();
}