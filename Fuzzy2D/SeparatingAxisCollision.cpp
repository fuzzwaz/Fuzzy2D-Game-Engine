#include "Collider.h"
#include "SeparatingAxisCollision.h"

using std::vector;

/*
	Description:
		Determines if two Polygon Colliders are colliding using Separating Axis Theorem

	Arguments:
		polygonA - The initial collider (order does not matter)
		polygonB - The other collider (order does not matter)

	Returns:
		bool - True if the colliders are colliding (overlapping)
*/
bool SeparatingAxisCollision::IsColliding(const ColliderInterface* polygonA, const ColliderInterface* polygonB)
{
	if (polygonA->IsCircular() && polygonB->IsCircular())
		return IsCircleColliding(polygonA, polygonB);

	auto perpsBeginA = polygonA->GetPerpendiculars()->cbegin();
	auto perpsEndA = polygonA->GetPerpendiculars()->cend();
	auto perpsBeginB = polygonB->GetPerpendiculars()->cbegin();
	auto perpsEndB = polygonB->GetPerpendiculars()->cend();

	Vector2 axis(0, 0);	
	while (perpsBeginA != perpsEndA || perpsBeginB != perpsEndB)
	{
		if (perpsBeginA != perpsEndA)
		{
			axis.x = perpsBeginA->x;
			axis.y = perpsBeginA->y;
			perpsBeginA++;
		}
		else
		{
			axis.x = perpsBeginB->x;
			axis.y = perpsBeginB->y;
			perpsBeginB++;
		}

		const Extents projectonExtentsA = CalculateMinMixProjection(axis, polygonA);
		const Extents projectonExtentsB = CalculateMinMixProjection(axis, polygonB);

		//If a single Separating axis is found, the two polygons can't possibly be colliding
		if (IsSeparatingAxis(projectonExtentsA, projectonExtentsB))
		{
			return false;
		}
	}

	return true;
}

bool SeparatingAxisCollision::IsCircleColliding(const ColliderInterface* circleA, const ColliderInterface* circleB)
{
	Vector2 distance = circleB->GetCenter() - circleA->GetCenter();
	double combinedRadius = circleA->GetRadius() + circleB->GetRadius();
	if (distance.SquaredMagnitude() <= combinedRadius * combinedRadius) //Opportunity to cache these results for later use
	{
		return true;
	}

	return false;
}

bool SeparatingAxisCollision::IsColliding(const Vector2& point, const ColliderInterface* polygonB)
{
	//Create a combined list of all of the axes we need to project on to perform the Separating Axis theorem
	auto perpsBeginB = polygonB->GetPerpendiculars()->cbegin();
	auto perpsEndB = polygonB->GetPerpendiculars()->cend();

	Vector2 axis(0, 0);
	while (perpsBeginB != perpsEndB)
	{
		axis.x = perpsBeginB->x;
		axis.y = perpsBeginB->y;

		const Extents projectonExtentsA = CalculateMinMixProjection(axis, point);
		const Extents projectonExtentsB = CalculateMinMixProjection(axis, polygonB);

		//If a single Separating axis is found, the two polygons can't possibly be colliding
		if (IsSeparatingAxis(projectonExtentsA, projectonExtentsB))
		{
			return false;
		}

		perpsBeginB++;
	}

	return true;
}

Vector2 SeparatingAxisCollision::CalculateCircleCollisionPoint(const ColliderInterface* circleA, const ColliderInterface* circleB)
{
	Vector2 distanceVector = circleB->GetCenter() - circleA->GetCenter();
	distanceVector.Normalize();

	return (distanceVector * circleA->GetRadius()) + circleA->GetPosition();
}

/*
	Description:
		Finds the specific vertices within each collider that are colliding. Averages them out as an approximate collision point.

	Arguments:
		polygonA - The initial collider (order does not matter)
		polygonB - The other collider (order does not matter)

	Returns:
		Vector2 - The approximate collision point in world coordinates
*/
Vector2 SeparatingAxisCollision::CalculateCollisionPoint(const ColliderInterface* polygonA, const ColliderInterface* polygonB)
{
	if (polygonA->IsCircular() && polygonB->IsCircular())
		return CalculateCircleCollisionPoint(polygonA, polygonB);

	vector<Vector2> collidingVertices;
	CalculateCollidingVertices(polygonA, polygonB, collidingVertices);
	CalculateCollidingVertices(polygonB, polygonA, collidingVertices);

	Vector2 collisionPoint(0, 0);
	if (collidingVertices.size() > 0)
	{
		for (int i = 0; i < collidingVertices.size(); i++)
		{
			collisionPoint = collisionPoint + collidingVertices.at(i);
		}
		return (collisionPoint / collidingVertices.size());
	}

	return ((polygonA->GetCenter() + polygonB->GetCenter()) / 2) + polygonA->GetCenter();
}

/*
	Description:
		Projects a Polygon Collider onto a specific axis to calculate its position on that axis

	Arguments:
		projectionVector - The axis that the collider is being projected onto
		polygon - The polygon being projected

	Returns:
		Extents - Holds the results of the projection in the form of a min/max pair
*/
Extents SeparatingAxisCollision::CalculateMinMixProjection(const Vector2& projectionVector, const ColliderInterface* polygon)
{
	Extents projectionMinMax;
	bool minSet = false, maxSet = false;

	const Vector2 relativePositionOffset = polygon->GetPosition();
	const auto vertices = polygon->GetVertices();
	for (Vector2 vertex : *vertices.get())
	{
		//Offset each vertex by the Polygon's position to convert from relative vertex coordinates to world coordinates
		vertex.x += relativePositionOffset.x;
		vertex.y += relativePositionOffset.y;

		const float dotProduct = vertex.DotProduct(projectionVector);
		if (!minSet || dotProduct < projectionMinMax.min)
		{
			minSet = true;
			projectionMinMax.min = dotProduct;
		}

		if (!maxSet || dotProduct > projectionMinMax.max)
		{
			maxSet = true;
			projectionMinMax.max = dotProduct;
		}
	}

	return projectionMinMax;
}

Extents SeparatingAxisCollision::CalculateMinMixProjection(const Vector2& projectionVector, const Vector2& point)
{
	Extents projectionMinMax;
	bool minSet = false, maxSet = false;

	const float dotProduct = point.DotProduct(projectionVector);
	projectionMinMax.min = dotProduct;
	projectionMinMax.max = dotProduct;

	return projectionMinMax;
}

/*
	Description:
		Takes each vertex in a Polygon Collider and determines which ones are colliding with another Polygon Collider

	Arguments:
		polygonA - The collider whose vertex points are being tested
		polygonB - The collider that is being tested against
		collidingVerticesA - A reference vector which is updated which the polygonA vertices that are colliding with polygonB
*/
void SeparatingAxisCollision::CalculateCollidingVertices(const ColliderInterface* polygonA, const ColliderInterface* polygonB, vector<Vector2>& collidingVerticesA)
{
	auto vertices = polygonA->GetVertices();
	for (int i = 0; i < vertices->size(); i++)
	{
		Vector2 point(vertices->at(i).x + polygonA->GetPosition().x, vertices->at(i).y + polygonA->GetPosition().y);
		if (IsColliding(point, polygonB))
		{
			collidingVerticesA.push_back(point);
		}
	}
}

/*
	Description:
		Compares two Extents to see if there is an overlap between them. If there is not, then a separating axis exists

	Arguments:
		projectionExtentsA - The extents of a polygon (order does not matter)
		projectionExtentsB - The extents of another polygon being checked against (order does not matter)

	Returns:
		bool - Whether or not a separating axis exited between the two extents
*/
bool SeparatingAxisCollision::IsSeparatingAxis(const Extents& projectionExtentsA, const Extents& projectionExtentsB)
{
	const float minA = projectionExtentsA.min, maxA = projectionExtentsA.max;
	const float minB = projectionExtentsB.min, maxB = projectionExtentsB.max;

	if ((minA <= maxB && minA >= minB) || (minB <= maxA && minB >= minA)) {
		return false;
	}
	
	return true;
}
