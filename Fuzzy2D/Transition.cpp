#include "Transition.h"

Transition::Transition(const std::shared_ptr<const Animation>& destination) : _destination(destination)
{

}

Transition::Transition(const Property& propertyId, const int& value, std::shared_ptr<const Animation> destination) : Transition(destination)
{
	AddProperty(propertyId, value);
}

/*
	Description:
		The Add Property functions add Property and int pairs to the _propertyValue vector.
		They are expected values that need to be met in order for the transition to be executed.
 */
void Transition::AddProperty(const Property& propertyId, const int& value)
{
	_propertyValues.push_back(std::make_pair(propertyId, value)); //emplace opportunity 
}

void Transition::AddProperty(const std::pair<Property, int>& transitionProperty)
{
	_propertyValues.push_back(transitionProperty);
}

void Transition::AddProperty(const std::vector<std::pair<Property, int>>& transitionProperties)
{
	_propertyValues.insert(_propertyValues.end(), transitionProperties.cbegin(), transitionProperties.cend());
}

/*
	Description:
		Goes through each property pairing in _propertyValues. Compares those values
		with the ones stored in the propertyController. If any of the values don't exactly match,
		returns false. As long as all of the values match, returns true.

	Arguments:
		propertyController - A list of properties for an object. Used to compare against _propertyValues

	Return:
		bool - Whether or not the animator should use this transition and go to the destination animation
 */
bool Transition::ShouldTransition(const PropertyController& propertyController) const
{
	bool shouldTransition = true;

	for (int j = 0; j < _propertyValues.size(); j++)
	{
		const auto& property = _propertyValues.at(j);
		const bool transitionPropertyMatched = propertyController.ComparePropertyValue(property.first, property.second);

		if (!transitionPropertyMatched)
		{
			shouldTransition = false;
			break;
		}
	}

	return shouldTransition;
}