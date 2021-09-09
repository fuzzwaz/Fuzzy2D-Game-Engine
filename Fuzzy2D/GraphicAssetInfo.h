//
//  GraphicAssetInfo.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2021 Ramy Fawaz. All rights reserved.
//

#pragma once

#include "Common.h"
#include "Vector2.h"

#include <SDL_render.h>
#include <string>

//Used to represent a Graphic Asset to be initialized at some future point
struct GraphicAssetInfo
{
	GraphicAssetInfo(const GraphicAssetInfo& source, const std::string& filePath, const int& textureCount)
	{
		*this = source;
		this->_FilePath = filePath;
		this->_TextureCount = textureCount;
	}

	GraphicAssetInfo(const GraphicAssetInfo& source, const std::string& filePath)
	{
		*this = source;
		this->_FilePath = filePath;
	}

	GraphicAssetInfo(const std::string& filePath, const int& count, const float& scale = 1, const float& speed = 1,
		const RenderingLayer& layer = RenderingLayer::UI, const bool& loop = true, const bool& percentBased = false,
		const SDL_RendererFlip& flip = SDL_RendererFlip::SDL_FLIP_NONE, const Vector2& offset = Vector2(-0.5, -0.5), const Vector2& rotationOffset = Vector2(0.5, 0.5))
		: _FilePath(filePath), _TextureCount(count), _TextureScale(scale), _AnimationSpeed(speed),
		_RenderingLayer(layer), _Looping(loop), _PercentageBased(percentBased), _FlipStyle(flip), _TextureOffset(offset), _TextureRotationOffset(rotationOffset) {}

	/* Texture File Information */
	std::string _FilePath = "Assets/"; //The path where the graphic(s) can be found
	int _TextureCount = 1; //The number of textures associate with the asset
	
	/* Rendering Information */
	float _TextureScale = 1; //The scale you want the texture to be scaled by while rendering
	SDL_RendererFlip _FlipStyle = SDL_RendererFlip::SDL_FLIP_NONE; //If the textures should be flipped
	RenderingLayer _RenderingLayer = RenderingLayer::UI;
	//The origin of each graphic is is the Top Left. This represents the desired offset from this origin to draw the textures.
	//-0.5, -0.5 Means half of the width and half of the width offset in the negative direction (left)
	Vector2 _TextureOffset = Vector2(-0.5, -0.5);
	Vector2 _TextureRotationOffset = Vector2(0.5, 0.5);//Textures rotate from their center position. This offsets from that rotational point

	/* Animation Information */
	float _AnimationSpeed = 1; //The speed at which the animation textures will be shuffled through
	bool _Looping = true; //Whether or not the asset should loop through its textures
	bool _PercentageBased = false; //The graphic animates vai a percentage instead of a timer based system
};