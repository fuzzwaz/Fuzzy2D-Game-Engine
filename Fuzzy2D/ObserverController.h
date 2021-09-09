//
//  ObserverController.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2021 Ramy Fawaz. All rights reserved.
//

#pragma once

#include <vector>
#include <memory>
#include <list>

class GameObject;
class GameObjectObserver;
enum class GameObjectEvent;

/*
	A controller component that can be added to any object that wants to be observed by a GameObjectObserver
*/
class ObserverController
{
public:
	void AddObserver(GameObjectObserver* observer) { _observers.push_back(observer); }
	void AddObserver(GameObjectObserver* observer, const std::list<std::shared_ptr<GameObject>>::iterator& objectId) { _observerPairs.emplace_back(observer, objectId); }

	void NotifyObservers(const GameObjectEvent& eventType) const;
	void NotifyObservers(const GameObjectEvent& eventType, const bool& begin) const;

private:
	/* Lists of observers that are observing the object holding this controller */
	std::vector<GameObjectObserver*> _observers;
	std::vector<std::pair<GameObjectObserver*, const std::list<std::shared_ptr<GameObject>>::iterator>> _observerPairs; //Observers who supply a specific iterator that can be used uniquely respond to an event
};	