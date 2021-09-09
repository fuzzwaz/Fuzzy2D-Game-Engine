//
//  ItemSpawner.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2021 Ramy Fawaz. All rights reserved.
//

#pragma once
#include "Item.h"

#include <vector>
#include <utility>

struct Vector2;

//Singleton used to randomly spawn at item at a specified position 
class ItemSpawner
{
public:
	void SpawnItem(const Vector2& position);

	static ItemSpawner& GetInstance();

private:
	ItemSpawner();
	ItemSpawner(const ItemSpawner&);
	void operator=(const ItemSpawner&);

	const int _itemBounceSpawnRate = 3; //Percent chance that a Bounce Item will spawn
	const int _itemHealthSpawnRate = 7; //Percent change that a Health Item will spawn

	std::vector<std::pair<const Item, const int>> _itemList;
};