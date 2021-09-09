#include "CollisionResponse.h"
#include "RigidBody.h"

double CollisionResponse::_ignoreResponseAngle = 90;

/*
	Description:
		Compares two rigidBodies to determine the suggested velocity to apply to the first rigidBody for a momentum based collision response

	Arguments:
		currentRigidBody - The first rigidBody. The response velocity is being calculated for this rigidBody specifically
		otherRigidBody - The rigidBody that currentRigidBody is colliding with
		collisionNormal - The normal for the collision. Starts at the collision point and faces collision direction

	Returns:
		Vector2 - The suggested impulse velocity that should be applied to the currentRigidBody as a result to its collision
*/

Vector2 CollisionResponse::CalculateResultingImpulseVelocity(const RigidBody& const currentRigidBody, const RigidBody& const otherRigidBody, const Vector2 collisionNormal)
{
	const double collisionAngle = currentRigidBody.GetVelocity().AngleBetween(collisionNormal);
	if (abs(collisionAngle) >= _ignoreResponseAngle)
		return Vector2(0, 0);

	Vector2 relativeVelocity = currentRigidBody.GetVelocity() - otherRigidBody.GetVelocity();

	const double polygonElasticity = currentRigidBody.GetElasticityCoefficient();
	const double polygonMass = currentRigidBody.GetInvertedMass();
	const double collidingMass = otherRigidBody.GetInvertedMass();
	
	//Calculating General Momentum Based Collision Response
	const double collisionResponseMagnitudeNumerator = (polygonElasticity + 1) * (relativeVelocity.DotProduct(collisionNormal)); // (e + 1) x (Vrel * N)
	const double collisionResponseMagnitudeDenominator = (polygonMass + collidingMass) * (collisionNormal.DotProduct(collisionNormal)); // (1/m1 + 1/m2) x (N * N)

	double collisionResponseMagnitude = 0;
	if (collisionResponseMagnitudeDenominator != 0)
		collisionResponseMagnitude = collisionResponseMagnitudeNumerator / collisionResponseMagnitudeDenominator;

	Vector2 collisionResponseVelocity = collisionNormal * (polygonMass * collisionResponseMagnitude * -1);

	//Determine the correct direction for the response
	if (collisionAngle < 0)
		collisionResponseVelocity * -1;

	return collisionResponseVelocity;
}