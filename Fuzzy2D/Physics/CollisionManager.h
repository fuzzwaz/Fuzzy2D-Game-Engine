//
//  CollisionManager.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2021 Ramy Fawaz. All rights reserved.
//

#pragma once

#include <vector>

class ColliderInterface;
struct Vector2;

/*
	Contains the list of all Colliders in a scene. Compares each Collider with another
	to determine if their is a Collision. If so, updates the Collision response information
	to be dealt with at a later time.
*/
class CollisionManager
{
public:
	void SimulateCurrentCollisions() const; //Runs through collision detection by comparing all of the colliders in _colliders

	void AddCollider(ColliderInterface* collider);
	void AddCollider(const std::vector<ColliderInterface*>& colliders);
	void RemoveCollider(ColliderInterface* collider);

	void RemoveAllColliders() { _colliders.clear(); }

	virtual ~CollisionManager();

private:
	std::vector<ColliderInterface*> _colliders; //List of all colliders that are considered for collision detection

	void HandleCollisionResponse(ColliderInterface* mainCollider, const ColliderInterface* collidingWith, const Vector2& collisionPoint) const;
	bool ShouldTestForCollision(const ColliderInterface* colliderA, const ColliderInterface* colliderB) const;
	bool TooFarApart(const ColliderInterface* colliderA, const ColliderInterface* colliderB) const;
};