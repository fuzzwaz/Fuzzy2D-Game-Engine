#include "DemoLevel.h"
#include "GameManager.h"
#include "GameObject.h"
#include "GameObjectRegistryLocator.h"
#include "InputManager.h"

/*
    Description:
        Without being initialized, GameManager is capable of rendering capabilities
 */
GameManager::GameManager()
{
    _camera = std::make_unique<ScrollingCamera>();
    _renderer = std::make_unique<Renderer>(_camera);
    GameObjectRegistryLocator::SetService(this);
}

/*
	Description:
		Constructs each of the engine domains relevant to the game and automatically starts the first level.
 */
void GameManager::Initialize()
{
    _collisionManager = std::make_unique<CollisionManager>();
    _soundManager = std::make_unique<SoundManager>();
    _userInterfaceManager = std::make_unique<UserInterfaceManager>();

    InitializeGameWorld();
}

/*
    Description:
        Constructs and connects engine components that are specific to a game level.
        The Level Manager loads a level and each of the other components respond to the specifics
        detailed from that level.
 */
void GameManager::InitializeGameWorld()
{
    _levelManager = std::make_unique<LevelManager>();
    _levelManager->LoadLevel(std::make_shared<DemoLevel>());

    InitializeLevel();
    InitializeCamera();
    
    _levelManager->StartLevel();
}

void GameManager::InitializeLevel()
{
    _levelManager->AddObserver(this);
    _levelManager->AddObserver(_soundManager.get());
    _levelManager->AddObserver(_userInterfaceManager.get());
    _collisionManager->AddCollider(_levelManager->GetCurrentLevelColliders());
}

/*
    Description:
        Specifies the size, shape, and position of the camera according to the current level
 */
void GameManager::InitializeCamera()
{
    _camera->SetCameraPosition(_levelManager->GetCurrentLevelCameraStartingPosition());
    _camera->SetLevelBoundaries(_levelManager->GetCurrentLevelTransform()->GetBounds());
    _camera->ResetPlayerPosition(_levelManager->GetCurrentLevelPlayerStartingPosition());
}

/*
    Description:
        Re-initializes relevant components to replay the current level while maintaining
        already loaded data from the initial initialization 
 */
void GameManager::RestartLevel()
{
    GameOver();
    _gameOver = false;
	_gameObjects.clear();
    _toBeDestroyedQueue.clear();
    _levelManager->Restart();
    _userInterfaceManager.reset(new UserInterfaceManager());
    _camera.reset(new ScrollingCamera());
    _renderer->SetCamera(_camera);

    InitializeLevel();
    InitializeCamera();

    _levelManager->StartLevel();
}

void GameManager::QuitGame()
{
    GameOver();
    _renderer.release();
    SDL_Quit();
}

void GameManager::GameOver()
{
    _levelManager->PauseLevel();
    _renderer->SetScreenShake(false);
    _gameOver = true;
    _gameObjects.clear();
    _collisionManager->RemoveAllColliders();
}

/*
    Description:
        Goes through the iterators in _toBeDestroyedQueue and removed them from the
        _gameObjects list. If they have colliders, unregisters them from the collision manager
 */
void GameManager::DestroyDeactivatedGameObjects()
{
    for (const auto& goIterator : _toBeDestroyedQueue)
    {
        ColliderInterface* associatedCollider = (*goIterator)->GetCollider();
        if (associatedCollider != nullptr)
            _collisionManager->RemoveCollider(associatedCollider);
        _gameObjects.erase(goIterator);
    }

    _toBeDestroyedQueue.clear();
}


void GameManager::Update(const InputState& inputState)
{
    /* Clear off Game Objects that were destroyed last frame */
    DestroyDeactivatedGameObjects();

    /* Simulate Collisions amongst all Game Objects so that the can respond during their Update calls */
    _collisionManager->SimulateCurrentCollisions();

    /* Update the level, camera, player, and all active Game Objects on the scene */
    _levelManager->Update();
    InputState worldCoordinateAdjustedInputState = inputState;
    worldCoordinateAdjustedInputState._CursorPosition = worldCoordinateAdjustedInputState._CursorPosition + _camera->GetPosition(); //Adjust the cursor position with the latest camera info

    for (auto goIterator = _gameObjects.begin(); goIterator != _gameObjects.end(); ++goIterator)
    {
        if ((*goIterator)->GetActive())
            (*goIterator)->Update(_camera->GetPosition(), worldCoordinateAdjustedInputState);
    }

    if (inputState._RestartPressed)
        RestartLevel();
}

/*
    Description:
        Renders all Game Objects and other relevant components in the level.
        Draws in RenderLayer order so that the higher Layers are drawn first.
 */
void GameManager::Render()
{
    _renderer->ClearScreen();

    if (_levelManager->GetCurrentLevelGraphicsController() != nullptr)
		_renderer->Render(_levelManager->GetCurrentLevelTransform(), _levelManager->GetCurrentLevelGraphicsController());

    for (auto it = _gameObjects.rbegin(); it != _gameObjects.rend(); it++)
    {
        auto graphicsController = (*it)->GetGraphicsController();
        if (graphicsController != nullptr && graphicsController->IsActive())
        {
            _renderer->Render((*it)->GetTransform(), graphicsController);
        }
    }

    _renderer->SwapFrameBuffers();
}

/*
    Description:
        Adds a new gameObject to the _gameObjects array.
        _gameObjects is sorted by RenderLayer so this function tries to maintain that sort.

        Attaches the usual GameObject observers and connects the object to the collision manager if
        it has a collider.

    Arguments:
		gameObject - The gameObject being passed over to the GameManager to manage
 */
void GameManager::AddGameObjectToScene(std::shared_ptr<GameObject> gameObject)
{
    auto newObjectIt = _gameObjects.end();
    if (gameObject->GetGraphicsController() != nullptr)
    {
        for (auto it = _gameObjects.begin(); it != _gameObjects.end(); it++)
        {
            const int renderLayer = static_cast<int>(gameObject->GetGraphicsController()->GetRenderingLayer());
            const int iteratorRenderLayer = static_cast<int>((*it)->GetGraphicsController()->GetRenderingLayer());
            if (renderLayer <= iteratorRenderLayer)
            {
                newObjectIt = it;
                break;
            }
        }
    }

    newObjectIt = _gameObjects.insert(newObjectIt, gameObject);
    gameObject->AddObserver(this, newObjectIt);
    gameObject->AddObserver(_soundManager.get(), newObjectIt);

    ColliderInterface* collider = gameObject->GetCollider();
    if (collider != nullptr)
        _collisionManager->AddCollider(collider);
}

void GameManager::Notify(const GameObjectEvent& eventType, const std::list<std::shared_ptr<GameObject>>::iterator& objectId)
{
    if (eventType == GameObjectEvent::DESTROYED)
    {
        _toBeDestroyedQueue.push_back(objectId);
    }
    else
    {
        Notify(eventType);
    }
}

void GameManager::Notify(const GameObjectEvent& eventType)
{
    if (eventType == GameObjectEvent::GAME_OVER || eventType == GameObjectEvent::VICTORY)
    {
        GameOver();
    }
}