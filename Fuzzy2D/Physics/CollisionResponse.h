//
//  CollisionResponse.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2021 Ramy Fawaz. All rights reserved.
//

#pragma once

#include "ColliderBaton.h"
#include "Vector2.h"

#include <vector>

class RigidBody;
class Collider;

//Compares two rigidBodies to determine the suggested velocity to apply to the first rigidBody for a momentum based collision response
class CollisionResponse
{
public:
	static Vector2 CalculateResultingImpulseVelocity(const RigidBody& currentRigidBody, const RigidBody& otherRigidBody, const Vector2 collisionNormal);

private:
	static double _ignoreResponseAngle; //Ignore collision response if the abs(angle) between the polygon and the collision is greater than this value
};


//Encapsulates relevant collision data needed for game objects to appropriately respond to all collisions each frame
struct CollisionResponseInfo
{
	CollisionResponseInfo() : _IsColliding(false), _NudgeDirection(Vector2(0, 0)), _ImpulseVector(Vector2(0, 0)) {}
	CollisionResponseInfo(bool colliding, Vector2 nD, Vector2 iV) : _IsColliding(colliding), _NudgeDirection(nD), _ImpulseVector(iV) {}

	bool _IsColliding = false;
	Vector2 _NudgeDirection; //The direction that the object should be nudged in order to resolve overlap
	Vector2 _ImpulseVector; //The immediate velocity to apply in order to respect the Momentum Based Collision Response calculations
	Vector2 _CollisionPoint; //Averaged value of all collisions
	std::vector<Vector2> _AllCollisionPoints; //List of all individual collisions 
	std::vector<ColliderBaton> _Batons;
};