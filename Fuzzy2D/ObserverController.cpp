#include "ObserverController.h"
#include "GameObjectObserver.h"

void ObserverController::NotifyObservers(const GameObjectEvent& eventType) const
{
    for (int i = 0; i < _observers.size(); i++)
    {
        _observers.at(i)->Notify(eventType);
    }

    for (int i = 0; i < _observerPairs.size(); i++)
    {
        _observerPairs.at(i).first->Notify(eventType, _observerPairs.at(i).second);
    }
}

void ObserverController::NotifyObservers(const GameObjectEvent& eventType, const bool& begin) const
{
    for (int i = 0; i < _observers.size(); i++)
    {
        _observers.at(i)->Notify(eventType, begin);
    }

    for (int i = 0; i < _observerPairs.size(); i++)
    {
        _observerPairs.at(i).first->Notify(eventType, begin);
    }
}