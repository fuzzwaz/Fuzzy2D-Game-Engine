//
//  GameObjectRegistryLocator.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2021 Ramy Fawaz. All rights reserved.
//

#pragma once

class GameObjectRegistryService;

/*
	Following the Service/Locator design pattern, this Locator allows a service to be set which
	registers new GameObjects to the scene.
*/
class GameObjectRegistryLocator
{
public:
	static void SetService(GameObjectRegistryService* service) { _service = service; }
	static GameObjectRegistryService* GetCreatorService() { return _service; }

private:
	static GameObjectRegistryService* _service;
};