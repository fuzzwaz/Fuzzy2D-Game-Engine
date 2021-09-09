#include "GameObject.h"
#include "Transform.h"

GameObject::GameObject() : GameObject(Vector2(0,0))
{
}

GameObject::GameObject(const Vector2& position, const Vector2& direction)
{
	_transform = std::make_shared<Transform>();
	_transform->SetOrigin(position);
	_transform->SetForwardVector(direction);
	_transform->_Collider.SetAssociatedRigidBody(&_transform->_RigidBody);
}

GameObject::GameObject(const GameObject& source)
{
	_transform = std::make_shared<Transform>();
	*_transform = *source._transform;
}
