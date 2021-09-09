#include "Common.h"
#include "Vector2.h"

#include <cmath>

bool CommonHelpers::AreEqual(double a, double b, const double acceptableDifference)
{
	const double absoluteDifference = abs(a - b);
	return   absoluteDifference <= acceptableDifference;
}

bool CommonHelpers::AreEqual(Vector2 a, Vector2 b, const double acceptableDifference)
{
	return AreEqual(a.x, b.x, acceptableDifference) && AreEqual(a.y, b.y, acceptableDifference);
}

Vector2 CommonHelpers::RandomOffset(int offsetMagnitude)
{
	int newX = rand() % offsetMagnitude;
	int newY = rand() % offsetMagnitude;

	if (rand() % 10 >= 5)
		newX *= -1;

	if (rand() % 10 >= 5)
		newY *= -1;

	return Vector2(newX, newY);
}