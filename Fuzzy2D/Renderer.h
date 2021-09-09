//
//  Renderer.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2021 Ramy Fawaz. All rights reserved.
//

#pragma once

#include "Texture.h"
#include "ScrollingCamera.h"

#include <memory>
#include <vector>

class GraphicsController;
class GraphicObject;
class Transform;
struct SDL_Window;
struct SDL_Renderer;

/*
	Wrapper class for SDL_Renderer. Manages all of the game's rendering needs including:
	 - Creating new SDL_Textures
	 - Screen Effects
	 - Drawing Textures to the Screen
*/
class Renderer final
{
public:
	Renderer(std::shared_ptr<const ScrollingCamera> camera);
	~Renderer();

	bool Initialize();

	void Render(const std::shared_ptr<const Transform>& transform, const std::shared_ptr<const GraphicsController>& graphicsController);
	void Render(const std::vector<Vector2>& points, const Vector2& origin);

	void ClearScreen();
	void SwapFrameBuffers();

	void SetScreenShake(const bool active);
	void SetCamera(std::shared_ptr<ScrollingCamera> camera) { _camera = camera; }

	static bool CreateTextureFromFile(Texture& newTexture, const std::string& filePath);

private:
	void RenderTexture(const Transform& transform, const std::shared_ptr<const Texture>& texture) const;
	Vector2 ConvertPointFromModelToCameraSpace(const Vector2 point, const Vector2 origin) const;
	Vector2 CalculateCameraCoordinatesForTexture(const std::shared_ptr<const Texture>& texture, const Vector2& worldSpacePosition, const Vector2& additionalOffset = Vector2(0,0)) const;
	void UpdateRenderingEffectOffset(const RenderingLayer& renderingLayer);

	SDL_Window* sdlWindow = nullptr; //The Gameplay Window as defined by SDL
	static SDL_Renderer* SDL_RENDERER; //The Underlying Renderer that this class communicates with

	std::shared_ptr<const ScrollingCamera> _camera = nullptr; //The camera which defines the "Camera Space" in which we render to

	Vector2 _renderingEffectOffset; //An offset which represents how textures are shifted due to active screen effects

	/* Screen Shake Effect */
	int _shakeActiveCount = 0; //How many callers are currently requesting a screen shake
	bool _screenShake = false; //Whether or not the renderer should adjust _renderingEffectOffset with a screen shake offset
	const int _screenShakeMagnitude = 7; //How intense the screen shake is. 0 Meaning no screen shake
	

};