//
//  PropertyController.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2021 Ramy Fawaz. All rights reserved.
//

#pragma once

#include "GameObjectProperties.h"

#include <unordered_map>

/*
	A class which manages a list of properties for any object. The "Property" enum is used as the
	key to identify which property is surveyed. Useful for keeping stats up to date (ex: Health)
	and also required by Animators to determine when to transition from one Animation to the next.
*/
class PropertyController
{
public:
	int GetPropertyValue(const Property& propertyId) const;
	void SetPropertyValue(const Property& propertyId, const int& value);
	bool ComparePropertyValue(const Property& propertyId, const int& value) const;

private:
	std::unordered_map<Property, int> _propertyMap;
};