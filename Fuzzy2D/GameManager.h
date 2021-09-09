//
//  GameManager.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2021 Ramy Fawaz. All rights reserved.
//

#pragma once

#include "CollisionManager.h"
#include "GameObjectObserver.h"
#include "GameObjectRegistryService.h"
#include "LevelManager.h"
#include "Renderer.h"
#include "ScrollingCamera.h"
#include "SoundManager.h"
#include "UserInterfaceManager.h"

#include <memory>
#include <list>
#include <vector>

class GameObject;
struct InputState;

/*
	Central hub of the game engine. Connects the major components including Physics, rendering, input,
	UI, and sound.
	
	Holds scene manager responsibilities with a list of Game Objects that get updated and rendered each frame.
 */
class GameManager final : public GameObjectObserver, public GameObjectRegistryService
{
public:
    GameManager();

    void Initialize();

    void QuitGame();
    
    void Update(const InputState& inputState);
    void Render();

    void Notify(const GameObjectEvent& eventType) override;
    void Notify(const GameObjectEvent& eventType, const std::list<std::shared_ptr<GameObject>>::iterator& objectId) override;

    void AddGameObjectToScene(std::shared_ptr<GameObject> gameObject) override;

private:
    void InitializeGameWorld();
    void InitializeLevel();
    void InitializeCamera();

    void DestroyDeactivatedGameObjects();

    void GameOver();
    void RestartLevel();


    /* Different Domains of the Engine */
    std::unique_ptr<Renderer> _renderer = nullptr;
    std::unique_ptr<UserInterfaceManager> _userInterfaceManager = nullptr;
    std::unique_ptr<SoundManager> _soundManager = nullptr;
    std::unique_ptr<LevelManager> _levelManager = nullptr;
    std::unique_ptr<CollisionManager> _collisionManager = nullptr;

    std::shared_ptr<ScrollingCamera> _camera = nullptr;

    std::list<std::shared_ptr<GameObject>> _gameObjects; //List of GameObjects being updated and rendered each frame. Sorted by RenderLayer to optimize rendering speed
    std::vector<std::list<std::shared_ptr<GameObject>>::iterator> _toBeDestroyedQueue; //List of GameObject that have gone out of use and should be destroyed

    bool _gameOver = false;
};
