#include "Common.h"
#include "Vector2.h"

#include <iostream>


bool Vector2::operator==(const Vector2& other) const
{
	return x == other.x && y == other.y;
}

Vector2 Vector2::operator+(const Vector2& other) const
{
	Vector2 result(x + other.x, y + other.y);
	return result;
}

Vector2 Vector2::operator-(const Vector2& other) const
{
	Vector2 result(x - other.x, y - other.y);
	return result;
}

Vector2 Vector2::operator*(const Vector2& other) const
{
	Vector2 result(x * other.x, y * other.y);
	return result;
}

Vector2 Vector2::operator*(const float& scalar) const
{
	Vector2 result(x * scalar, y * scalar);
	return result;
}

Vector2 Vector2::operator/(const float& scalar) const
{
	Vector2 result(x / scalar, y / scalar);
	return result;
}

float Vector2::Magnitude() const
{
	const float var = (x * x) + (y * y);
	return sqrt(var);
}

float Vector2::SquaredMagnitude() const
{
	return (x * x) + (y * y);
}

float Vector2::AngleBetween(const Vector2& other) const
{
	float dotProduct = this->DotProduct(other);
	float magnitudeProduct = this->Magnitude() * other.Magnitude();
	if (magnitudeProduct != 0)
	{
		const float radians = acos(dotProduct / magnitudeProduct);
		return CommonHelpers::RadToDeg(radians);
	}
	return 0;

}

float Vector2::DotProduct(const Vector2& other) const
{
	return (x * other.x) + (y * other.y);
}

Vector2 Vector2::Normal() const
{
	if (x == 0 && y == 0)
		return *this;

	Vector2 normal = *this;
	const float magnitude = Magnitude();
	normal.x /= magnitude;
	normal.y /= magnitude;

	return normal;
}

void Vector2::Normalize()
{
	*this = Normal();
}
