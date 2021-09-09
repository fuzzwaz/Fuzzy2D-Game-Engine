//
//  GameObject.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2021 Ramy Fawaz. All rights reserved.
//

#pragma once

#include "GameObjectObserver.h"
#include "ObserverController.h"
#include "Vector2.h"

#include <memory>

class ColliderInterface;
class GraphicsController;
class InputState;
class Transform;

/*
	The GameObject class is the base block in which all other objects are formed. By default, a GameObject only requires
	a transform. Subclasses of GameObject can add physics, graphics, and other componentized scripts. 
 */
class GameObject
{
public:
	GameObject();
	GameObject(const Vector2& position, const Vector2& direction = Vector2(0, -1));
	GameObject(const GameObject& source);
	virtual ~GameObject() = default;

	virtual void Update(const Vector2& cameraPosition, const InputState& input) = 0;
	void AddObserver(GameObjectObserver* observer, const std::list<std::shared_ptr<GameObject>>::iterator& objectId) { _observerController.AddObserver(observer, objectId); }

	/* Getters */
	bool GetActive() const { return _active; } //Active game objects get Update calls from the GameManager
	const std::shared_ptr<const Transform> GetTransform() const { return _transform; }
	virtual std::shared_ptr<const GraphicsController> GetGraphicsController() const = 0; //Returning nullptr means that the GameObject has no graphics
	virtual ColliderInterface* GetCollider() = 0; //Returning nullptr means that the GameObject has no colliders

	/* Setters */
	void SetIsActive(const bool& active) { _active = active; }

protected:
	std::shared_ptr<Transform> _transform = nullptr; //The position, size, and movement information of the object
	ObserverController _observerController;

private:
	bool _active = true; //Active game objects get Update calls from the GameManager
};