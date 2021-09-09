//
//  SeparatingAxisCollision.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2021 Ramy Fawaz. All rights reserved.
//

#pragma once

#include <vector>

class ColliderInterface;

//Represents the extents of a one dimensional line in the form or a min/max pair. Helper struct for Separating Axis Collision Calculations
struct Extents
{
	Extents() = default;
	Extents(float mn, float mx) : min(mn), max(mx) {}

	bool operator==(const Extents& other) const { return min == other.min && max == other.max; }

	float min = 0;
	float max = 0;
};

//Utilizes Separating Axis Theorem to determine if and where two Polygon Colliders are colliding
namespace SeparatingAxisCollision
{
	bool IsColliding(const Vector2& point, const ColliderInterface* polygonB);
	bool IsColliding(const ColliderInterface* polygonA, const ColliderInterface* polygonB);
	bool IsCircleColliding(const ColliderInterface* circleA, const ColliderInterface* circleB);

	Vector2 CalculateCollisionPoint(const ColliderInterface* polygonA, const ColliderInterface* polygonB); //Approximates collision point by averaging colliding vertices
	Vector2 CalculateCircleCollisionPoint(const ColliderInterface* circleA, const ColliderInterface* circleB);

	Extents CalculateMinMixProjection(const Vector2& projectionVector, const ColliderInterface* polygon);
	Extents CalculateMinMixProjection(const Vector2& projectionVector, const Vector2& point);
	bool IsSeparatingAxis(const Extents& projectionExtentsA, const Extents& projectionExtentsB);
	void CalculateCollidingVertices(const ColliderInterface* polygonA, const ColliderInterface* polygonB, std::vector<Vector2>& collidingVerticesA);
}