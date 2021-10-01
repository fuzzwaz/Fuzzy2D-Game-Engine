//
//  GameObjectRegistryService.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2021 Ramy Fawaz. All rights reserved.
//

#pragma once

#include <memory>

class GameObject;

/*
	Following the Service/Locator design pattern, this service registers new GameObjects to the scene.
	Typically this entails adding it to the active GameObject list and associating its graphics with the renderer
	and its colliders with the collision manager.

	However, different service types can be set so that registry can be freely defined
*/
class GameObjectRegistryService
{
public:
	virtual void AddGameObjectToScene(std::shared_ptr<GameObject> gameObject) = 0;
};