#include "Common.h"
#include "Polygon.h"
#include "Vector2.h"

Polygon::Polygon()
{
	_vertices.reset(new std::vector<Vector2>());
	_perpendiculars.reset(new std::vector<Vector2>());
}

void Polygon::operator=(const Polygon& source)
{
	if (this == &source)
		return;

	_vertices->clear();
	_perpendiculars->clear();

	_vertices->insert(_vertices->end(), source._vertices->cbegin(), source._vertices->cend());
	_perpendiculars->insert(_perpendiculars->end(), source._perpendiculars->cbegin(), source._perpendiculars->cend());
}

void Polygon::AddVertexPoint(float x, float y)
{
	AddVertexPoint(Vector2(x, y));
}

void Polygon::AddVertexPoint(const Vector2& vertex)
{
	_vertices->push_back(vertex);
	_numOfVertices++;
	_dirtyPerpendiculars = true; //New vertex means a new edge has been added. Perpendiculars need to be recalculated
	RecalculateCenterPoint();
}

void Polygon::AddVertexPoint(const std::vector<Vector2>& vertices)
{
	for (auto it = vertices.begin(); it != vertices.end(); it++)
	{
		AddVertexPoint(*it);
	}
}

/*
	Description:
		A getter which can trigger a Perpendicular recalculation if marked as dirty

	Returns:
		shared_ptr<vector<Vector2>> - Pointer to the cached perpendiculars for this Collider
*/
const std::shared_ptr<const std::vector<Vector2>> Polygon::GetPerpendiculars() const
{
	if (_dirtyPerpendiculars)
	{
		RecalculatePerpendicularVectors();
	}

	return _perpendiculars;
}


/*
	Description:
		Rotates each vertex point by "degrees" degrees clockwise. Sets the dirty flag for perpendiculars.

	Arguments:
		degrees - Clockwise rotatation
*/
void Polygon::Rotate(float degrees)
{
	const float radians = CommonHelpers::DegToRad(degrees);

	for (int i = 0; i < _vertices->size(); i++)
	{
		float newX = (_vertices->at(i).x * cos(radians)) + (_vertices->at(i).y * sin(radians) * -1);
		float newY = (_vertices->at(i).x * sin(radians)) + (_vertices->at(i).y * cos(radians));

		_vertices->at(i).x = newX;
		_vertices->at(i).y = newY;
	}

	if (degrees != 0)
		_dirtyPerpendiculars = true;
}

/*
	Description:
		Resets the current Perpendicular list. Goes through each edge in the polygon and calculates a
		clockwise perpendicular vector. Adds that vector to _perpendiculars.

		Clears the dirty flag
*/
void Polygon::RecalculatePerpendicularVectors() const
{
	_perpendiculars->clear();

	if (_vertices->size() >= 2)
	{
		for (int i = 0; i < _vertices->size() - 1; i++)
		{
			_perpendiculars->push_back(ClockwisePerpendicularVector(_vertices->at(i), _vertices->at(i + 1)));
		}
		//Wrap the last vertex to the first for the final polygon perpendicular
		_perpendiculars->push_back(ClockwisePerpendicularVector(_vertices->at(_vertices->size() - 1), _vertices->at(0)));
	}

	_dirtyPerpendiculars = false;
}

void Polygon::RecalculateCenterPoint()
{
	float minX = INT_MAX, minY = INT_MAX;
	float maxX = INT_MIN, maxY = INT_MIN;

	for (int i = 0; i < _vertices->size(); i++)
	{
		Vector2 vertex(_vertices->at(i));

		if (vertex.x < minX)
			minX = vertex.x;
		if (vertex.x > maxX)
			maxX = vertex.x;
		if (vertex.y < minY)
			minY = vertex.y;
		if (vertex.y > maxY)
			maxY = vertex.y;
	}

	Vector2 sizeVector(maxX - minX, maxY - minY);
	_center.x = (sizeVector.x / 2) + minX;
	_center.y = (sizeVector.y / 2) + minY;
}

Vector2 ClockwisePerpendicularVector(const Vector2& pointA, const Vector2& pointB)
{
	const Vector2 clockwiseVector(pointB.x - pointA.x, pointB.y - pointA.y);
	return ClockwisePerpendicularVector(clockwiseVector);
}

Vector2 ClockwisePerpendicularVector(const Vector2& vector)
{
	return Vector2(vector.y, -1 * vector.x);
}

Vector2 CounterClockwisePerpendicularVector(const Vector2& pointA, const Vector2& pointB)
{
	const Vector2 counterClockwiseVector(pointB.x - pointA.x, pointB.y - pointA.y);
	return CounterClockwisePerpendicularVector(counterClockwiseVector);
}

Vector2 CounterClockwisePerpendicularVector(const Vector2& vector)
{
	return Vector2(-1 * vector.y, vector.x);
}