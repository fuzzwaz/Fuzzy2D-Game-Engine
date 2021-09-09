//
//  UserInterfaceManager.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2021 Ramy Fawaz. All rights reserved.
//

#pragma once

#include "GameObjectObserver.h"
#include "Vector2.h"

#include <memory>
#include <unordered_map>
#include <utility>

class GraphicObject;
class GraphicsController;
class InputState;
class Transform;

//Manages the spawning and initialization of all User Interface objects 
class UserInterfaceManager : public GameObjectObserver
{
public:
	UserInterfaceManager();
	void Notify(const GameObjectEvent& eventType) override;

private:
	const Vector2 _centerScreenPosition;

	//Map which keeps track of which Events correspond to which UI objects need to be spawned
	std::unordered_map<GameObjectEvent, std::pair<const std::shared_ptr<const GraphicObject>, const Vector2&>> _eventMap;
};

