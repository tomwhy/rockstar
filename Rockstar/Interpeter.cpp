#include "Interpeter.h"
#include "PreProcessor.h"
#include "Utils.h"


Interpeter::Interpeter(const std::string& filePath) : _runtime(), _compiler(filePath)
{
}

void Interpeter::run()
{
	_runtime.run(_compiler.getCode());
}