//
//  Vector2.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2015 Ramy Fawaz. All rights reserved.
//

#pragma once

//Helper class representing a two dimensional point or vector
struct Vector2
{
	Vector2() : x(0), y(0) {}
	Vector2(const float& _x, const float& _y) : x(_x), y(_y) {}

	void Normalize();

	float Magnitude() const;
	float SquaredMagnitude() const;
	float AngleBetween(const Vector2& other) const;
	float DotProduct(const Vector2& other) const;
	Vector2 Normal() const;

	bool operator==(const Vector2& other) const;
	Vector2 operator+(const Vector2& other) const;
	Vector2 operator-(const Vector2& other) const;
	Vector2 operator*(const Vector2& other) const;
	Vector2 operator*(const float& scalar) const;
	Vector2 operator/(const float& scalar) const;

	float x = 0;
	float y = 0;
};