#include "Collider.h"
#include "NullRigidBody.h"

using std::vector;

Collider::Collider()
{
	//By default, Colliders don't ignore any other Collider type
	for(int i = 0; i < ColliderType::ALL; i++)
		_ignoreTypes[i] = false;

	_Baton._Type = ColliderType::ENVIRONMENT;
}

/*
	Description:
		Checks the _ignoreTypes array to see if a specific ColliderType is being ignored.
		Used to determine if the CollisionManager should skip over a collision test
*/
bool Collider::IsIgnoring(ColliderType type) const
{
	const int index = static_cast<int>(type);
	return _ignoreTypes[index];
}

/*
	Description:
		Gets a copy of the RigidBody associated with the Collider.
		Used to determine appropriate collision response information (things like mass, current velocity, etc..)
*/
RigidBody Collider::GetAssociatedRigidBody() const
{
	if (_rigidBody != nullptr)
		return *_rigidBody;

	return NullRigidBody(); //Returns a Null Dummy Rigidbody in the case that there is nothing associated with the Collider.
}

Vector2 Collider::GetCenter() const
{
	return _origin + _Polygon.GetCenter();
}

void Collider::SetColliderType(const ColliderType& type)
{
	_type = type;
	_Baton._Type = type;
}

void Collider::SetColliderIgnoreTypes(std::vector<ColliderType> ignoreTypes)
{
	for (int i = 0; i < ignoreTypes.size(); i++)
	{
		int index = static_cast<int>(ignoreTypes.at(i));
		_ignoreTypes[index] = true;
	}
}

/*
	Description:
		Accumulates Collision Response information for every Update call.
		This is because a Collider can collide with multiple other objects per frame.

	Arguments:
		info - The newest set up CollisionResponseInfo. Soon to be added to the pile of others 
*/
void Collider::UpdateCollisionResponseInfo(const CollisionResponseInfo& info)
{
	_responseInfo._IsColliding = _responseInfo._IsColliding || info._IsColliding;
	_responseInfo._ImpulseVector = _responseInfo._ImpulseVector + info._ImpulseVector;
	_responseInfo._NudgeDirection = _responseInfo._NudgeDirection + info._NudgeDirection;
	_responseInfo._CollisionPoint = _responseInfo._CollisionPoint + info._CollisionPoint;
	_responseInfo._AllCollisionPoints.insert(_responseInfo._AllCollisionPoints.end(), info._AllCollisionPoints.begin(), info._AllCollisionPoints.end());
	_responseInfo._Batons.insert(_responseInfo._Batons.end(), info._Batons.begin(), info._Batons.end());
}

/*
	Description:
		Resets the response info to its default "No current collision" state
*/
void Collider::ClearCollisionResponseInfo()
{
	_responseInfo._IsColliding = false;
	_responseInfo._ImpulseVector = Vector2(0, 0);
	_responseInfo._NudgeDirection = Vector2(0, 0);
	_responseInfo._CollisionPoint = Vector2(0, 0);
	_responseInfo._AllCollisionPoints.clear();
	_responseInfo._Batons.clear();
}