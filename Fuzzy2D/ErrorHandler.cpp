#include <cassert>
#include <iostream>

#include "ErrorHandler.h"

void ErrorHandler::Assert(const bool& EXPRESSION)
{
	assert(EXPRESSION);
}

void ErrorHandler::Assert(const bool& EXPRESSION, const std::string& MESSAGE)
{
	if (!EXPRESSION)
	{
		std::cout << MESSAGE << std::endl;
		assert(false);
	}
}