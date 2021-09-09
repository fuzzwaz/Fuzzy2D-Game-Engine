#include "PropertyController.h"
#include "ErrorHandler.h"

int PropertyController::GetPropertyValue(const Property& propertyId) const
{
	if (_propertyMap.find(propertyId) == _propertyMap.end())
	{
		ErrorHandler::Assert(false, "Asked for a property which has not yet been assigned.");
		return 0;
	}

	return _propertyMap.at(propertyId);
}

/*
	Description:
		If a propertyId is not found in the _propertyMap, a new one is created. Otherwise,
		the old value is overwritten
*/
void PropertyController::SetPropertyValue(const Property& propertyId, const int& value)
{
	if (_propertyMap.find(propertyId) == _propertyMap.end())
	{
		_propertyMap.insert({ propertyId, value });
		return;
	}

	_propertyMap[propertyId] = value;
}

bool PropertyController::ComparePropertyValue(const Property& propertyId, const int& value) const
{
	const int currentValue = GetPropertyValue(propertyId);
	if (currentValue == value)
		return true;

	return false;
}