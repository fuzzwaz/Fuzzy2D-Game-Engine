#include "ErrorHandler.h"
#include "NullRigidBody.h"

NullRigidBody::NullRigidBody()
{
	SetSpeed(0);
	SetDecelerationSpeed(0);
	SetInvertedMass(1);
	SetElasticityCoefficient(0);
	SetInputVelocity(Vector2(0, 0));
	SetAcceleration(Vector2(0, 0));
}

Vector2 NullRigidBody::ApplyMovementForces(const int frameSteps)
{
	ErrorHandler::Assert(true, "Trying to Apply Movement Forces to a null rigid body");
	return Vector2(0, 0);
}

void NullRigidBody::AddImpulseVelocity(const Vector2& velocity)
{
	ErrorHandler::Assert(true, "Trying to add an Impulse Velocity to a null rigid body");
	return;
}