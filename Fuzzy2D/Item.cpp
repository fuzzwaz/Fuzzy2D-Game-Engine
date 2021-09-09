#include "Item.h"
#include "GraphicAssetResources.h"
#include "TimedDestructionController.h"
#include "Transform.h"
#include "Rectangle.h"

#include "ColliderResources.h"

Item::Item(const Item& source) : GraphicObject(source)
{
	_itemResponseEvent = source._itemResponseEvent;
	_transform->_Collider.SetAssociatedRigidBody(&_transform->_RigidBody);
}

Item::Item(const Rectangle& bounds, const GraphicAssetInfo& media, const Collider& collider, const GameObjectEvent& event) : GraphicObject(media)
{
	_transform->SetSize(bounds._Width, bounds._Height);
	_transform->_Collider = collider;
	_itemResponseEvent = event;
	_destructionController->SetDestructionTime(_destructionTime);
}

/*
	Description:
		Creates a new active copy of an Item with a new position

	Arguments:
		position - The initial position for the cloned GraphicObject in world coordinates
		direction - Where the clone is facing. Defaults to up (0, -1)
*/
std::shared_ptr<GraphicObject> Item::Clone(const Vector2& position, const Vector2& direction) const
{
	std::shared_ptr<Item> clone = std::make_shared<Item>(*this);
	clone->SetPosition(position);
	clone->SetIsActive(true);

	return clone;
}

void Item::Update(const Vector2& cameraPosition, const InputState& input)
{
	GraphicObject::Update(cameraPosition, input);

	/* Check if colliding with the Player. */
	const auto collisionInfo = _transform->_Collider.GetCollisionResponseInfo();
	const auto playerColliderFound = std::find_if(collisionInfo._Batons.cbegin(), collisionInfo._Batons.cend(), 
		[](const ColliderBaton& baton) { return baton._Type == ColliderType::PLAYER; });
	if (collisionInfo._IsColliding && playerColliderFound != collisionInfo._Batons.cend())
	{
		/* If so, "Consume" the item by firing off it's response event and removing it from the scene */
		_observerController.NotifyObservers(_itemResponseEvent);
		_observerController.NotifyObservers(GameObjectEvent::DESTROYED);
		SetIsActive(false);
	}
}

ColliderInterface* Item::GetCollider()
{
	return &_transform->_Collider;
}