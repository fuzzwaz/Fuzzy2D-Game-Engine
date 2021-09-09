//
//  Rectangle.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2015 Ramy Fawaz. All rights reserved.
//

#pragma once

#include "Vector2.h"

//Helper class representing a rectangle
struct Rectangle
{
	Rectangle() = default;
	Rectangle(float w, float h) : _Width(w), _Height(h) {}
	Rectangle(float x, float y, float w, float h) : _Width(w), _Height(h)
	{
		_Origin.x = x;
		_Origin.y = y;
	}

	bool operator==(const Rectangle& other) const;

	Vector2 Center() const;

	float _Width = 0;
	float _Height = 0;
	Vector2 _Origin;
};