//
//  RigidBody.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2021 Ramy Fawaz. All rights reserved.
//

#pragma once

#include "Vector2.h"

class RigidBody
{
public:
	virtual Vector2 ApplyMovementForces(const int frameSteps = 1);
	virtual void AddImpulseVelocity(const Vector2& velocity);

	/* Setters */
	void SetSpeed(const float& speed) { _speed = speed; }
	void SetMinCollisionImpulseMagnitude(const float& magnitude) { _minimumCollisionImpulseMagnitude = magnitude; }
	void SetInputVelocity(const Vector2& velocity) { _inputVelocity = velocity; }
	void SetImpulseVelocity(const Vector2& velocity) { _impulseVelocity = velocity; }
	void SetAcceleration(const Vector2& acceleration) { _acceleration = acceleration; }
	void SetDecelerationSpeed(const float& decelerationSpeed) { _decelerationSpeed = decelerationSpeed; }
	void SetInvertedMass(const float& iMass) { _mass = iMass; }
	void SetElasticityCoefficient(const float& e);

	/* Getters */
	float GetSpeed() const { return _speed; }
	float GetMinCollisionImpulseMagnitude() const { return _minimumCollisionImpulseMagnitude; }
	float GetInvertedMass() const { return _mass; } //Returns the inverse mass (1/mass) where an immovable object is has a _mass of 0
	float GetElasticityCoefficient() const { return _collisionElasticity; } //Returns a value from 0 to 1. 0 is perfectly inelastic (no bounce) while 1 is perfectly elastic (bounce)
	Vector2 GetVelocity() const { return _inputVelocity + _impulseVelocity; }
	
private:
	float _mass = 0.25; //Stored as inverse mass (1/mass) where an immovable object is has a _mass of 0
	float _collisionElasticity = 0.75;//From 0 to 1. 0 is perfectly inelastic (no bounce) while 1 is perfectly elastic (bounce)

	float _speed = 750; //Maximum speed applied due to acceleration
	float _maxImpulseSpeed = 3000; //Maximum speed that can be applied by an impulse (typically collisions)
	float _decelerationSpeed = 2000.0;

	float _minimumCollisionImpulseMagnitude = 0; //Overrides collision response magnitude by requiring each response velocity to at least have this magnitude. Useful if you want and object to overreact to collisions
	Vector2 _inputVelocity; //Gradual velocity change. Usually caused by continual acceleration
	Vector2 _impulseVelocity; //Instant velocity change. Usually caused by collisions
	Vector2 _acceleration;
	
	void ApplyCurrentAcclerationToVelocity(const int frameSteps = 1);
	void ApplyDeceleration(Vector2& velocity, const int frameSteps = 1);

	Vector2 CalculateDisplacementForCurrentVelocity(const int frameSteps = 1);
};