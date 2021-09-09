#include "TimedDestructionController.h"
#include "GameObjectObserver.h"


/*
	Description:
		Called by the controller owner to check if it's time to be destroyed, otherwise the destruction controller
		will never update.

		Starts the timer if _destructionTime is greater than 0. If the timer runs out, notifies observers that
		it's time to start the destruction process for that object.

	Returns:
		bool - Whether or not the object is about to be destroyed. GameObjects have time to react to this news
		as the GameManager will not destroy the object until the start of the next frame
*/
bool TimedDestructionController::TimeIsUp()
{
	if (_destroyed)
		return true;

	if (!_destructionTimer.GetActive() && _destructionTime > 0)
		_destructionTimer.Start();

	const bool timeHasLapsed = _destructionTimer.GetActive() && _destructionTimer.GetSeconds() >= _destructionTime;
	if (!_destroyed && timeHasLapsed)
	{
		_destroyed = true;
		_observerController.NotifyObservers(GameObjectEvent::DESTROYED);
		return true;
	}

	return false;
}

void TimedDestructionController::operator=(const TimedDestructionController& source)
{
	_destructionTime = source._destructionTime;
}