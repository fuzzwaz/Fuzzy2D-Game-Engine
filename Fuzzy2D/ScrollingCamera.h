//
//  ScrollingCamera.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2021 Ramy Fawaz. All rights reserved.
//

#pragma once

#include "Rectangle.h"

//Keeps track of the Main Camera's coordinate system so that other domains have access to camera space.
class ScrollingCamera
{
public:
	ScrollingCamera();
	ScrollingCamera(float x, float y, float w, float h);

	void Update(const Vector2& playerPosition);

	Vector2 GetPosition() const;
	Vector2 GetDisplacement() const { return _bounds._Origin - _cameraPreviousPosition; }

	void ResetPlayerPosition(const Vector2& playerPosition);
	void SetLevelBoundaries(int hBoundary, int vBoundary);
	void SetLevelBoundaries(Rectangle boundaries);
	void SetCameraPosition(const Vector2& position);

private:
	//Returns the direction specific tigger values that specify if the player is in the right position for the camera to scroll
	inline float GetEastMovementTrigger();
	inline float GetWestMovementTrigger();
	inline float GetNorthMovementTrigger();
	inline float GetSouthMovementTrigger();

	Rectangle _bounds;
	Vector2 _playerPreviousPosition;
	Vector2 _cameraPreviousPosition;

	//The east edge boundary of camera space.The camera can't go beyond this point. Boundary is ignored when set to -1
	int _horizontalBoundry = -1;
	//The south edge boundary of camera space.The camera can't go beyond this point. Boundary is ignored when set to -1
	int _verticalBoundry = -1;

	//The distance the player must travel from the center of the screen in order for the camera to begin scrolling
	const int _movementTriggerSizeHorizontal = 100;
	const int _movementTriggerSizeVertical = 70;
};