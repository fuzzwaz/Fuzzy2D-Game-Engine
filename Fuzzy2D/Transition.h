//
//  Transition.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2021 Ramy Fawaz. All rights reserved.
//

#pragma once

#include "GameObjectProperties.h"
#include "PropertyController.h"

#include <vector>
#include <memory>
#include <utility>

class Animation;

//The middleman between one Animation to the other. Used to determine if it's time to switch between Animations
class Transition
{
public:
	Transition(const std::shared_ptr<const Animation>& destination);
	Transition(const Property& propertyId, const int& value, std::shared_ptr<const Animation> destination);

	void AddProperty(const Property& propertyId, const int& value);
	void AddProperty(const std::pair<Property, int>& transitionProperty);
	void AddProperty(const std::vector<std::pair<Property, int>>& transitionProperties);

	bool ShouldTransition(const PropertyController& propertyController) const;

	std::shared_ptr<const Animation> GetDestination() const { return _destination; }

private:
	std::shared_ptr<const Animation> _destination  = nullptr; //A pointer to the destination Animation that is being transition to
	std::vector<std::pair<Property, int>> _propertyValues; //A list of property that are used to determine when a transition is ready to move onto its destination animation.
};