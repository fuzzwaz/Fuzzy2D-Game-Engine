#include "CollisionResponse.h"
#include "ErrorHandler.h"
#include "Transform.h"

Transform::Transform() : _aabb(Rectangle(0,0,1,1))
{
}

Transform::Transform(Rectangle aabb, Vector2 forward) : _aabb(aabb)
{
	SetForwardVector(forward);
	_Collider.SetPosition(_aabb._Origin);
}


void Transform::Move(const float x, const float y)
{
	SetPosition(Vector2(_aabb._Origin.x + x, _aabb._Origin.y + y));
}

void Transform::Move(const Vector2& pt)
{
	SetPosition(Vector2(_aabb._Origin.x + pt.x, _aabb._Origin.y + pt.y));
}

void Transform::Nudge(const Vector2& direction, const float& magnitude)
{
	Vector2 NudgeVector = direction * magnitude;
	Move(NudgeVector);
}

void Transform::SetOrigin(float x, float y)
{
	SetPosition(Vector2(x, y));
}

void Transform::SetOrigin(Vector2 pt)
{
	SetPosition(Vector2(pt.x, pt.y));
}

void Transform::SetSize(float width, float height)
{
	
	_aabb._Width = fmax(width, 1.0);
	_aabb._Height = fmax(height, 1.0);
}

/*
	Description:
		Sets the forward vector property of the Transform. 
		Will also update the _orientation property to match the new forward vector if requested.

	Arguments:
		vector - New forward vector direction
		alignOrientationToForward - When true, sets orientation to match forward vector direction
*/
void Transform::SetForwardVector(const Vector2& vector, const bool alignOrientationToForward)
{
	if (vector == Vector2(0, 0))
	{
		ErrorHandler::Assert(true, "Forward Vector cannot be set to the Zero vector.");
		return;
	}

	const int vectorMagnitude = vector.Magnitude();
	if (vectorMagnitude > 1)
		_forwardVector = vector.Normal();
	else
		_forwardVector = vector;

	if (alignOrientationToForward)
	{
		const Vector2 up(0, -1);
		const Vector2 right(1, 0);

		double angle = up.AngleBetween(_forwardVector);

		if (right.DotProduct(_forwardVector) < 0)
			angle *= -1;

		SetOrientation(angle);
	}
}

/*
	Description:
		Sets the orientation property of the Transform.
		Will also update the _forwardVector property to match the new forward vector if requested.

	Arguments:
		rotationValue - New orientation angle. Clockwise is positive
		alignForwardToOrientation - When true, sets forward vector to match the new orientation
*/
void Transform::SetOrientationAngle(const double& rotationValue, const bool alignForwardToOrientation)
{
	SetOrientation(rotationValue);

	if (alignForwardToOrientation)
	{
		const double radians = CommonHelpers::DegToRad(rotationValue);
		const Vector2 up(0, -1);

		_forwardVector.x = (up.x * cos(radians)) - (up.y * sin(radians));
		_forwardVector.y = (up.x * sin(radians)) + (up.y * cos(radians));
	}
}

/*
	Description:
		Wrapper helper function to set the _orientation property.
		Automatically rotates the ColliderContainer everytime the orientation changes.

	Arguments:
		rotationValue - New orientation value. 
*/
void Transform::SetOrientation(const double& rotationValue)
{
	const double orientationChange = rotationValue - _orientation;

	if (orientationChange != 0)
	{
		_Collider.Rotate(orientationChange);
	}
	_orientation = rotationValue;
}

void Transform::SetPosition(const Vector2& position)
{
	_aabb._Origin = position;
	_Collider.SetPosition(position);
}

/*
	Description:
		Updates the RigidBody according to the results of the current Collision
*/
std::vector<ColliderBaton> Transform::ResolveCollisions()
{
	CollisionResponseInfo responseInfo = _Collider.GetCollisionResponseInfo();
	if (responseInfo._IsColliding)
	{
		Nudge(responseInfo._NudgeDirection.Normal() * -1); //Nudges the transform away from the collision to fix overlap

		//Rigidbodies can specify a minimum magnitude that must be applied to them in the case of a collision
		if (responseInfo._ImpulseVector.Magnitude() < _RigidBody.GetMinCollisionImpulseMagnitude())
		{
			responseInfo._ImpulseVector.Normalize();
			responseInfo._ImpulseVector = responseInfo._ImpulseVector * _RigidBody.GetMinCollisionImpulseMagnitude();
		}
		_RigidBody.AddImpulseVelocity(responseInfo._ImpulseVector); //Applies an impulse vector as a result of the collision
	}
	auto batons = responseInfo._Batons;
	_Collider.ClearCollisionResponseInfo();

	return batons;
}
