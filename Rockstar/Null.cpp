#include "Null.h"
#include "Number.h"
#include "String.h"
#include "Mysterious.h"
#include "Boolean.h"
#include "Array.h"
#include "InterpeterExceptions.h"

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

std::shared_ptr<IVariable> Null::subtract(std::shared_ptr<IVariable> other)
{
	if (std::dynamic_pointer_cast<Number>(other) != nullptr)
	{
		std::shared_ptr<Number> right = std::dynamic_pointer_cast<Number>(other);

		return std::make_shared<Number>(-std::stold(right->toString()));
	}
	else if (std::dynamic_pointer_cast<Null>(other) != nullptr)
	{
		return std::make_shared<Number>(0); // 0 - 0 = 0
	}
	else
	{
		return std::make_shared<Mysterious>();
	}
}

std::shared_ptr<IVariable> Null::add(std::shared_ptr<IVariable> other)
{
	if (std::dynamic_pointer_cast<Number>(other) != nullptr)
	{
		std::shared_ptr<Number> right = std::dynamic_pointer_cast<Number>(other);

		return std::make_shared<Number>(std::stold(right->toString()));
	}
	else if (std::dynamic_pointer_cast<Null>(other) != nullptr)
	{
		return std::make_shared<Number>(0); // 0 + 0 = 0
	}
	else
	{
		return std::make_shared<Mysterious>();
	}
}

std::shared_ptr<IVariable> Null::multiply(std::shared_ptr<IVariable> other)
{
	if (std::dynamic_pointer_cast<Number>(other) != nullptr)
	{
		return std::make_shared<Number>(0);
	}
	else if (std::dynamic_pointer_cast<String>(other) != nullptr)
	{
		return std::make_shared<String>("");
	}
	else if (std::dynamic_pointer_cast<Null>(other) != nullptr)
	{
		return std::make_shared<Number>(0); // 0 * 0 = 0
	}
	else
	{
		return std::make_shared<Mysterious>();
	}
}

std::shared_ptr<IVariable> Null::divide(std::shared_ptr<IVariable> other)
{
	if (std::dynamic_pointer_cast<Number>(other) != nullptr)
	{
		return std::make_shared<Number>(0);
	}
	else
	{
		return std::make_shared<Mysterious>();
	}
}

bool Null::equal(std::shared_ptr<IVariable> other)
{
	if (std::dynamic_pointer_cast<Mysterious>(other) != nullptr ||
		std::dynamic_pointer_cast<String>(other) != nullptr)
	{
		return false;
	}
	else if (std::dynamic_pointer_cast<Number>(other) != nullptr ||
			std::dynamic_pointer_cast<Array>(other) != nullptr)
	{
		return Number(0).equal(other);
	}
	else if (std::dynamic_pointer_cast<Boolean>(other) != nullptr)
	{
		return Boolean(false).equal(other);
	}
	else // null
	{
		return true;
	}
}

bool Null::less(std::shared_ptr<IVariable> other)
{
	if (std::dynamic_pointer_cast<Number>(other) != nullptr ||
		std::dynamic_pointer_cast<Array>(other) != nullptr)
	{
		return Number(0).less(other);
	}
	else // null
	{
		return IVariable::less(other);
	}
}
