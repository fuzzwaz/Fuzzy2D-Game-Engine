//
//  GameObjectObserver.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2021 Ramy Fawaz. All rights reserved.
//

#pragma once

#include <list>
#include <memory>

class GameObject;

/* List of Events that a GameObjectObserver can respond to */
enum class GameObjectEvent
{
	DESTROYED,
	POWERED_UP,
	LEVEL_START,
	GAME_OVER,
	VICTORY
};

/*
	Classes that want to observe GameObjects just need to inherit GameObjectObserver and define the Notify functions that
	correspond with the events they are interested in responding to.
*/
class GameObjectObserver
{
public:
	virtual void Notify(const GameObjectEvent& eventType, const bool begin)
	{
		if (begin)
			Notify(eventType);
	}

	virtual void Notify(const GameObjectEvent& eventType, const std::list<std::shared_ptr<GameObject>>::iterator& objectId)
	{
		Notify(eventType);
	}

	virtual void Notify(const GameObjectEvent& eventType)
	{
		 
	}
};
