//
//  Transform.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2021 Ramy Fawaz. All rights reserved.
//

#pragma once

#include "Collider.h"
#include "Rectangle.h"
#include "RigidBody.h"
#include "Vector2.h"

#include <vector>

/*
	Handles Movement and Rotation for game objects. 
	Each Transform has a RigidBody to handle movement physics and a Collider Container which determines how it should response to Collisions
*/
class Transform
{
public:
	Transform();
	Transform(Rectangle aabb, Vector2 forward = Vector2(0, -1));

	/* Movement */
	void Move(const float x, const float y);
	void Move(const Vector2& pt);
	void Nudge(const Vector2& direction, const float& magnitude = 7.5);

	/* Setters */
	void SetOrigin(float x, float y);
	void SetOrigin(Vector2 pt);
	void SetSize(float width, float height);
	void SetForwardVector(const Vector2& vector, const bool alignOrientationToForward = true);
	void SetOrientationAngle(const double& rotationValue, const bool alignForwardToOrientation = true); //Positive angles represent clockwise turns. Can update the forward vector to match new orientation.

	/* Getters */
	Vector2 GetOrigin() const { return _aabb._Origin; }
	Rectangle GetBounds() const { return _aabb; }
	Vector2 GetForwardVector() const { return _forwardVector; }
	double GetOrientationAngle() const { return _orientation; }
	
	std::vector<ColliderBaton> ResolveCollisions();

	RigidBody _RigidBody;
	Collider _Collider;

private:
	Rectangle _aabb;
	Vector2 _forwardVector;
	double _orientation = 0.0; //Best not to set directly as it skips over Collider rotation. Use the "SetOrientation" helper function instead

	void SetOrientation(const double& rotationValue);
	void SetPosition(const Vector2& position);
};