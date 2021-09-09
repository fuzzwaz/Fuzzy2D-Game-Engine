//
//  ColliderResources.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2021 Ramy Fawaz. All rights reserved.
//

#include "Collider.h"

#pragma once

//A master list of all of the Colliders used in the game
namespace Resources
{
	struct Colliders
	{
		static Collider ENVIRONMENT()
		{
			Collider environment;
			environment.SetIsStatic(true);
			environment.SetColliderType(ColliderType::ENVIRONMENT);
			environment._Baton._Type = ColliderType::ENVIRONMENT;
			return environment;
		}
	};
}