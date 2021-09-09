#include "Level.h"

void Level::Restart()
{
	_levelStarted = false;
	_observersAlertedOfLevelStart = false;
}


void Level::Update(GameObjectObserver& observer)
{
	if (_levelStarted && !_observersAlertedOfLevelStart)
	{
		observer.Notify(GameObjectEvent::LEVEL_START);
		_observersAlertedOfLevelStart = true;
	}
}