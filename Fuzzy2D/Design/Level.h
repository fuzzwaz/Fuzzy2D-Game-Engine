//
//  Level.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2021 Ramy Fawaz. All rights reserved.
//

#pragma once

#include "GameObjectObserver.h"
#include "MultiTextureGraphicsController.h"
#include "Transform.h"

class MultiTextureGraphicsController;
class Collider;

/*
	Template of how a game Level is consumed in the Game Engine. Level specific information
	is left for derived classes to define.

	By default, Level's support delayed start time. This functionality can be ignored by derived classes 
*/
class Level
{
public:
	virtual ~Level() = default;

	virtual void Update(GameObjectObserver& observer);
	virtual void Start() { _levelStarted = true; }
	virtual void Restart();

	virtual void LoadLevel() = 0;
	virtual bool LevelHasFinished() const = 0;

	/* Getters */
	virtual Vector2 GetCameraStart() const = 0;
	virtual Vector2 GetPlayerStart() const = 0;
	virtual std::shared_ptr<const Transform> GetTransform() const = 0;
	virtual std::shared_ptr<const GraphicsController> GetGraphicsController() const = 0;
	virtual std::vector<ColliderInterface*> GetLevelColliders() = 0;

	bool LevelHasStarted() const { return _levelStarted; }

private:
	bool _observersAlertedOfLevelStart = false;
	bool _levelStarted = false;
};