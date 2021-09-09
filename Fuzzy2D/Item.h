//
//  Item.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2021 Ramy Fawaz. All rights reserved.
//

#pragma once

#include "AnimatedSingleTextureGraphicsController.h"
#include "GraphicObject.h"
#include "Vector2.h"

class Collider;
class TimedDestructionController;
struct GraphicAssetInfo;
struct Rectangle;

//A Graphic Object with a collider and collider response event. When a Player collides with an Item, and event is kicked off which results in a property change for the Player
class Item : public GraphicObject
{
public:
	Item(const Item& source);
	Item(const Rectangle& bounds, const GraphicAssetInfo& media, const Collider& collider, const GameObjectEvent& event);

	std::shared_ptr<GraphicObject> Clone(const Vector2& position, const Vector2& direction = Vector2(0, -1)) const override;

	void Update(const Vector2& cameraPosition, const InputState& input) override;

	inline ColliderInterface* GetCollider() override;

private:
	void Initialize();

	GameObjectEvent _itemResponseEvent = GameObjectEvent::POWERED_UP; //The event that occurs as a response to a collision with the Player
	const float _destructionTime = 15; //How long the item stays present in the scene before being destroyed
};