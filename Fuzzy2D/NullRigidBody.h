//
//  NullRigidBody.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2021 Ramy Fawaz. All rights reserved.
//

#pragma once

#include "RigidBody.h"

//Useful as a dummy Rigidbody in the case that one is not set or not needed.
//For example, Trigger Colliders don't respond to collisions and so don't need associated RigidBodies 
class NullRigidBody : public RigidBody
{
public:
	NullRigidBody();

	Vector2 ApplyMovementForces(const int frameSteps = 1) override;
	void AddImpulseVelocity(const Vector2& velocity) override;
};