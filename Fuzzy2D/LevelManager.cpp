#include "LevelManager.h"
#include "ErrorHandler.h"
#include "Transform.h"

LevelManager::LevelManager()
{

}

void LevelManager::LoadLevel(const std::shared_ptr<Level>& level)
{
	_currentLevel = level;
	_currentLevel->LoadLevel();
}

void LevelManager::StartLevel()
{
	ErrorHandler::Assert(_currentLevel != nullptr, "There is no level currently loaded");
	if (_currentLevel != nullptr)
		_currentLevel->Start();
}

void LevelManager::PauseLevel()
{
	_levelPaused = true;
}

void LevelManager::UnPauseLevel()
{
	_levelPaused = false;
}



void LevelManager::Update()
{
	ErrorHandler::Assert(_currentLevel != nullptr, "There is no level currently loaded");
	if (_currentLevel != nullptr && !_levelPaused)
		_currentLevel->Update(*this);
}

void LevelManager::Restart()
{
	if (_currentLevel != nullptr)
		_currentLevel->Restart();
	_levelPaused = false;
	_observers.clear();
}

void LevelManager::Notify(const GameObjectEvent& eventType)
{
	for (int i = 0; i < _observers.size(); i++)
	{
		_observers.at(i)->Notify(eventType);
	}
}