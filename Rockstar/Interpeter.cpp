#include "Interpeter.h"
#include "PreProcessor.h"
#include "Utils.h"


Interpeter::Interpeter(const std::string& filePath) : _runtime(), _file(filePath, std::ios::in), _parser(Utils::getDefsPath())
{
	_file.unsetf(std::ios::skipws);
}

//std::vector<Statement> Interpeter::parseFile(const std::string& filePath)
//{
//	Parser parser(Utils::getDefsPath());
//	return parser.parse(PreProcessor::readLines(filePath));
//}

void Interpeter::run()
{
	std::string line;
	while (std::getline(_file, line))
	{
		line = PreProcessor::removeComments(line);
		line = PreProcessor::removeSingleQuotes(line);

		if (line.empty())
			continue;

		_runtime.run(_parser.parseLine( line));
	}
}