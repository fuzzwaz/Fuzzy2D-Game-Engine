//
//  ErrorHandler.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2015 Ramy Fawaz. All rights reserved.
//

#pragma once

#include <string>

//An assert helper class which allows for asserts to be paired with specific warning messages
struct ErrorHandler
{
	static void Assert(const bool& EXPRESSION);
	static void Assert(const bool& EXPRESSION, const std::string& MESSAGE);
};