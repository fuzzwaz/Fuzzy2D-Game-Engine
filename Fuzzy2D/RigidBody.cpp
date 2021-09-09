#include "RigidBody.h"
#include "Common.h"

#include <math.h>

/*
	Description:
		Applies all pending movement related forces onto the RigidBody including acceleration, velocity, and collision responses.

	Arguments:
		frameSteps - Controls the number of frames that are simulated. Defaults to 1.

	Returns:
		Vector2 - Representing the total resulting displacement vector for all of the simulated frames.
*/
Vector2 RigidBody::ApplyMovementForces(const int frameSteps)
{
	ApplyCurrentAcclerationToVelocity(frameSteps);
	return CalculateDisplacementForCurrentVelocity(frameSteps);
}

/*
	Description:
		Applies the current acceleration to update velocity

	Arguments:
		frameSteps - Controls the number of frames that are simulated. Defaults to 1.
*/
void RigidBody::ApplyCurrentAcclerationToVelocity(const int frameSteps)
{
	const Vector2 velocityChange = _acceleration * (frameSteps * FRAME_LENGTH);

	if (velocityChange.Magnitude() > 0)
	{
		_inputVelocity.x += velocityChange.x;
		_inputVelocity.y += velocityChange.y;

		//Make sure velocity can never be greater than the set speed for the RigidBody
		if (_inputVelocity.Magnitude() > _speed)
			_inputVelocity = _inputVelocity.Normal() * _speed;
	}
	else if (_inputVelocity.Magnitude() > 0)
	{
		//If no motion is being applied but the RigidBody still has velocity, naturally decelerate until fully stopped
		ApplyDeceleration(_inputVelocity, frameSteps);
	}

	//Impulse Vectors are always decelerating
	ApplyDeceleration(_impulseVelocity, frameSteps);
}

/*
	Description:
		Brings given velocity ref closer to zero according to _decelerationSpeed

	Arguments:
		velocity - A reference to the velocity value to decelerate
		frameSteps - Controls the number of frames that are simulated. Defaults to 1.
*/
void RigidBody::ApplyDeceleration(Vector2& velocity, const int frameSteps)
{
	const double deceleration = _decelerationSpeed * (frameSteps * FRAME_LENGTH);
	const Vector2 decelerationVector = velocity.Normal() * -1;
	const Vector2 currentVelocity = velocity;

	velocity.x += decelerationVector.x * deceleration;
	const bool xVelocityPassedZero = (currentVelocity.x > 0 && velocity.x < 0) || (currentVelocity.x < 0 && velocity.x > 0);

	if (xVelocityPassedZero)
		velocity.x = 0;

	velocity.y += decelerationVector.y * deceleration;
	const bool yVelocityPassedZero = (currentVelocity.y > 0 && velocity.y < 0) || (currentVelocity.y < 0 && velocity.y > 0);

	if (yVelocityPassedZero)
		velocity.y = 0;
}

/*
	Description:
		Uses velocity values to calculate a proposed position displacement  

	Arguments:
		frameSteps - Controls the number of frames that are simulated. Defaults to 1.

	Returns:
		Vector2 - Position displacement
*/
Vector2 RigidBody::CalculateDisplacementForCurrentVelocity(const int frameSteps)
{
	Vector2 totalVelocity = _inputVelocity + _impulseVelocity;

	if (totalVelocity.Magnitude() > _maxImpulseSpeed)
		totalVelocity = totalVelocity.Normal() * _maxImpulseSpeed;

	const Vector2 positionChange = totalVelocity * (frameSteps * FRAME_LENGTH);
	return positionChange;
}

/*
	Description:
		Adds an instance velocity force to the rigidBody.

	Arguments:
		velocity - The magnitude & direction of the velocity force to be applied
*/
void RigidBody::AddImpulseVelocity(const Vector2& velocity)
{
	_impulseVelocity.x += velocity.x;
	_impulseVelocity.y += velocity.y;

	//cout << "Impulse Velocity: ( " << velocity.x << " , " << velocity.y << " )" << endl;

	if (_impulseVelocity.Magnitude() > _maxImpulseSpeed)
	{
		_impulseVelocity = _impulseVelocity.Normal() * _maxImpulseSpeed;
	}
}

void RigidBody::SetElasticityCoefficient(const float& e)
{
	if (e < 0)
		_collisionElasticity = 0;
	else if (e > 1)
		_collisionElasticity = 1;
	else
		_collisionElasticity = e;
}
