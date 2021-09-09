//
//  LevelManager.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2021 Ramy Fawaz. All rights reserved.
//

#pragma once

#include "Collider.h"
#include "GameObjectObserver.h"
#include "Level.h"
#include "Transform.h"

/*
	Keeper of all of the level specific information. Used to get data from the current level,
	load a new level, and notify observers of level events.
 */
class LevelManager : public GameObjectObserver
{
public:
	LevelManager();
	void LoadLevel(const std::shared_ptr<Level>&);
	void StartLevel();
	void PauseLevel();
	void UnPauseLevel();

	void Update();
	void Restart();

	void AddObserver(GameObjectObserver* observer) { _observers.push_back(observer); }
	void Notify(const GameObjectEvent& eventType) override;

	/* Getters */
	Vector2 GetCurrentLevelCameraStartingPosition() const { return _currentLevel->GetCameraStart(); }
	Vector2 GetCurrentLevelPlayerStartingPosition() const { return _currentLevel->GetPlayerStart(); }
	std::shared_ptr<const Transform> GetCurrentLevelTransform() const { return _currentLevel->GetTransform(); }
	std::shared_ptr<const GraphicsController> GetCurrentLevelGraphicsController() const { return _currentLevel->GetGraphicsController(); }
	std::vector<ColliderInterface*> GetCurrentLevelColliders() const { return _currentLevel->GetLevelColliders(); }

private:
	std::shared_ptr<Level> _currentLevel = nullptr;
	std::vector<GameObjectObserver*> _observers;

	bool _levelPaused = false;
};