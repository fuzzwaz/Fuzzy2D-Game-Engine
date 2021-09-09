#include "Common.h"
#include "ScrollingCamera.h"

ScrollingCamera::ScrollingCamera() : ScrollingCamera(0,0, SCREEN_WIDTH, SCREEN_HEIGHT)
{
	
}

ScrollingCamera::ScrollingCamera(float x, float y, float w, float h)
{
	_bounds._Origin.x = x;
	_bounds._Origin.y = y;
	_bounds._Width = w;
	_bounds._Height = h;
	_cameraPreviousPosition = _bounds._Origin;
}

Vector2 ScrollingCamera::GetPosition() const
{ 
	return _bounds._Origin;
}

void ScrollingCamera::ResetPlayerPosition(const Vector2& playerPosition)
{
	_playerPreviousPosition = playerPosition;
}

void ScrollingCamera::SetLevelBoundaries(int hBoundary, int vBoundary)
{
	_horizontalBoundry = hBoundary;
	_verticalBoundry = vBoundary;
}

void ScrollingCamera::SetLevelBoundaries(Rectangle boundaries)
{
	SetLevelBoundaries(boundaries._Width, boundaries._Height);
}


void ScrollingCamera::SetCameraPosition(const Vector2& position)
{
	_bounds._Origin.x = position.x;
	_bounds._Origin.y = position.y;
}

/*
	Description:
		Checks the player's position to determine if the camera should scroll.
		If so, displaces the camera by the given x and y values.
*/
void ScrollingCamera::Update(const Vector2& playerPosition)
{
	_cameraPreviousPosition = _bounds._Origin;
	const int x = playerPosition.x - _playerPreviousPosition.x;
	const int proposedXDisplacement = _bounds._Origin.x + x;
	const bool isWithinHorizontalBounds = (proposedXDisplacement >= 0 && proposedXDisplacement + _bounds._Width <= _horizontalBoundry);

	if (_horizontalBoundry == -1 || isWithinHorizontalBounds)
	{
		const bool playerHitEastTrigger = proposedXDisplacement - _bounds._Origin.x > 0 && playerPosition.x >= GetEastMovementTrigger();
		const bool playerHitWestTrigger = proposedXDisplacement - _bounds._Origin.x < 0 && playerPosition.x <= GetWestMovementTrigger();

		if (playerHitEastTrigger || playerHitWestTrigger)
		{
			_bounds._Origin.x = proposedXDisplacement;
		}
	}
	
	const int y = playerPosition.y - _playerPreviousPosition.y;
	const int proposedYDisplacement = _bounds._Origin.y + y;
	const bool isWithinVerticalBounds = (proposedYDisplacement >= 0 && proposedYDisplacement + _bounds._Height <= _verticalBoundry);

	if (_verticalBoundry == -1 || isWithinVerticalBounds)
	{
		const bool playerHitSouthTrigger = proposedYDisplacement - _bounds._Origin.y > 0 && playerPosition.y >= GetSouthMovementTrigger();
		const bool playerHitNorthTrigger = proposedYDisplacement - _bounds._Origin.y < 0 && playerPosition.y <= GetNorthMovementTrigger();

		if (playerHitSouthTrigger || playerHitNorthTrigger)
		{
			_bounds._Origin.y = proposedYDisplacement;
		}
	}

	_playerPreviousPosition = playerPosition;
}

inline float ScrollingCamera::GetEastMovementTrigger()
{
	return _bounds.Center().x + _movementTriggerSizeHorizontal;
}

inline float ScrollingCamera::GetSouthMovementTrigger()
{
	return _bounds.Center().y + _movementTriggerSizeVertical;
}

inline float ScrollingCamera::GetWestMovementTrigger()
{
	return _bounds.Center().x - _movementTriggerSizeHorizontal;
}

inline float ScrollingCamera::GetNorthMovementTrigger()
{
	return _bounds.Center().y - _movementTriggerSizeVertical;
}