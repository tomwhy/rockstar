#include "RunTime.h"


RunTime::RunTime() :_globalScope()
{

}

void RunTime::run(const std::vector<std::unique_ptr<ICodeBlock>>& code)
{
	for (size_t i = 0; i < code.size(); i++)
	{
		code[i]->execute(_globalScope);
	}
}

void RunTime::run(std::unique_ptr<ICodeBlock> line)
{
	line->execute(_globalScope);
}
