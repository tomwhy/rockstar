#include "SplitStatement.h"
#include "InterpeterException.h"
#include "Array.h"
#include "String.h"
#include <vector>

SplitStatement::SplitStatement(std::shared_ptr<IExpression> exp, std::shared_ptr<VariableName> dest, std::shared_ptr<IExpression> argument) :IModifyStatement(exp, dest, argument)
{

}

std::shared_ptr<IVariable> SplitStatement::modify(Scope& scope)
{
	std::shared_ptr<Array> res;
	std::shared_ptr<IVariable> value = _exp->evaluate(scope);
	if (value->type() != "String")
		throw InterpeterException("Can only split strings");

	std::string str = value->toString();

	if (_argument == nullptr)
	{
		res = std::make_shared<Array>("0", value->getAt("0"));
		for (int i = 1; i < str.size(); i++)
		{
			std::string idx = std::to_string(i);
			res->setAt(idx, value->getAt(idx));
		}
	}
	else
	{
		std::string delim = _argument->evaluate(scope)->toString();
		size_t offset = 0;
		int idx = 0;
		std::vector<std::string> elements;
		size_t delimLoc;
		do
		{
			delimLoc = str.find(delim, offset);
			elements.push_back(str.substr(offset, delimLoc - offset));
			offset = delimLoc + delim.size();
		} while (delimLoc != std::string::npos);

		res = std::make_shared<Array>("0", std::make_shared<String>(elements[0]));
		for (int i = 1; i < elements.size(); i++)
		{
			std::string idx = std::to_string(i);
			res->setAt(idx, std::make_shared<String>(elements[i]));
		}

	}
	
	return res;
}
