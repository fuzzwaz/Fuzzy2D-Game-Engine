#include "CollisionManager.h"
#include "CollisionResponse.h"
#include "ColliderInterface.h"
#include "RigidBody.h"
#include "SeparatingAxisCollision.h"
#include "Vector2.h"

#include <algorithm>

using std::vector;
using std::shared_ptr;

/*
	Description:
		Runs through collision detection by comparing all of the colliders in _colliders.
		If a collision is detected, initiates collision response calculations and stores the results
		to be handled at a later point.
*/
void CollisionManager::SimulateCurrentCollisions() const
{
	for (int current = 0; current < _colliders.size(); current++)
	{
		ColliderInterface* currentCollider = _colliders.at(current);
		if (currentCollider == nullptr)
			continue;

		for (int other = current + 1; other < _colliders.size(); other++)
		{
			ColliderInterface* otherCollider = _colliders.at(other);
			if (otherCollider == nullptr)
				continue;

			const bool shouldTestForCollision = ShouldTestForCollision(currentCollider, otherCollider);
			if (shouldTestForCollision)
			{
				const bool IsColliding = SeparatingAxisCollision::IsColliding(currentCollider, otherCollider);

				if (IsColliding)
				{
					const Vector2 collisionPoint = SeparatingAxisCollision::CalculateCollisionPoint(currentCollider, otherCollider);
					HandleCollisionResponse(currentCollider, otherCollider, collisionPoint);
					HandleCollisionResponse(otherCollider, currentCollider, collisionPoint);
				}
			}

		}
	}
}

/*
	Description:
		Compares the Rigidbodies of both Colliders to determine the appropriate collision response for the Main COllider.
		Stores that response in the Main Colliders to be handled at a future point.

	Arguments
		mainCollider - The Collider that the response is being calculated for
		collidingWith - The Collider that is used for response math but is left unchanged
		collisionPoint - Where the two Colliders are colliding. Also needed for response information calculation
*/
void CollisionManager::HandleCollisionResponse(ColliderInterface* mainCollider, const ColliderInterface* collidingWith, const Vector2& collisionPoint) const
{
	CollisionResponseInfo responseInfo; //Creates a CollisionResponseInfo struct with all relevant response information
	Vector2 collisionNormal = collisionPoint - mainCollider->GetPosition();
	collisionNormal.Normalize();

	responseInfo._IsColliding = true;
	responseInfo._Batons.push_back(collidingWith->GetBaton());
	responseInfo._CollisionPoint = collisionPoint;
	responseInfo._AllCollisionPoints.push_back(collisionPoint);

	if (!mainCollider->IsStatic() && !mainCollider->IsTrigger() && !collidingWith->IsTrigger()) //Certain Colliders don't respond to impulse velocities
	{
		const Vector2 resultingCollisionVelocity = CollisionResponse::CalculateResultingImpulseVelocity(mainCollider->GetAssociatedRigidBody(), collidingWith->GetAssociatedRigidBody(), collisionNormal);
		responseInfo._ImpulseVector = resultingCollisionVelocity;
		responseInfo._NudgeDirection = collisionNormal;
	}

	mainCollider->UpdateCollisionResponseInfo(responseInfo); //Updates the collider with the latest CollisionResponseInfo struct
}

/*
	Description:
		Compares properties of two colliders to determine if it's worth trying to determine
		if they are colliding. 

	Arguments
		colliderA - The first collider
		colliderB - The second collider. Order does not matter
*/
bool CollisionManager::ShouldTestForCollision(const ColliderInterface* colliderA, const ColliderInterface* colliderB) const
{
	if (TooFarApart(colliderA, colliderB))
		return false;

	const bool shouldIgnore = colliderA->IsIgnoring(colliderB->GetColliderType()) || colliderB->IsIgnoring(colliderA->GetColliderType());
	const bool isSelf = colliderA == colliderB;
	const bool bothStatic = colliderA->IsStatic() && colliderB->IsStatic();
	const bool oneIsInactive = !colliderA->IsActive() || !colliderB->IsActive();
	const bool shouldInclude = !(shouldIgnore || isSelf || bothStatic || oneIsInactive);

	return shouldInclude;
}

/*
	Description:
		Each Collider has a Min Collision Distance. Colliders outside of this distance are ignored
		during Collision Detection. This function takes the Max Min Collision Distance of the two colliders
		and checks if they are outside of that range.

	Arguments
		colliderA - The first collider
		colliderB - The second collider. Order does not matter
*/
bool CollisionManager::TooFarApart(const ColliderInterface* colliderA, const ColliderInterface* colliderB) const
{
	const Vector2 Distance(colliderA->GetCenter() - colliderB->GetCenter());
	const double minDistance = std::max(colliderA->GetMinimumCollisionDistance(), colliderB->GetMinimumCollisionDistance());
	const auto squaredMagnitude = Distance.SquaredMagnitude(); //Avoid square root for optimization purposes

	if (squaredMagnitude > minDistance)
		return true;

	return false;
}


void CollisionManager::AddCollider(ColliderInterface* collider)
{
	auto foundIt = std::find(_colliders.cbegin(), _colliders.cend(), collider);

	if (foundIt == _colliders.cend())
	{
		_colliders.push_back(collider);
	}
}

void CollisionManager::AddCollider(const std::vector<ColliderInterface*>& colliders)
{
	for (auto& interface : colliders)
		AddCollider(interface);
}


void CollisionManager::RemoveCollider(ColliderInterface* collider)
{
	auto foundIt = std::find(_colliders.begin(), _colliders.end(), collider);
	if (foundIt != _colliders.cend())
	{
		auto backCollider = _colliders.back();
		(*foundIt) = backCollider;
		_colliders.pop_back();
	}
}

CollisionManager::~CollisionManager()
{
	_colliders.clear();
}