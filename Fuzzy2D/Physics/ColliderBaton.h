//
//  ColliderBaton.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2021 Ramy Fawaz. All rights reserved.
//

#pragma once

#include "Common.h"
#include "Vector2.h"

/*
	A lightweight "baton" that is passed from one collider to the other when colliding.
	The minimum amount of information that the other collider needs to know about the original collider
	to determine an appropriate response.
 */
struct ColliderBaton
{
	ColliderType _Type = ColliderType::ENVIRONMENT; //The general "group" that the collider is a part of
	ObjectId _Id = ObjectId::ENVIRONMENT; //The specific identification of what the collider is
	int _Value = 0; //A general purpose value that changes meaning depending on _Type and _Id.
};
