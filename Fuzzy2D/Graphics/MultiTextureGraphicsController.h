//
//  MultiTextureGraphicsController.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2021 Ramy Fawaz. All rights reserved.
//

#pragma once

#include "GraphicsController.h"

#include <string>
#include <memory>
#include <vector>

/*
	Graphics controller for objects that require multitude of textures to be displayed all at once. They are not animated.
	Because they are not animated, the Update function is left unimplemented.

	Textures can be offset from one another and support parallax layers.Useful for unanimated background sprites.
 */
class MultiTextureGraphicsController : public GraphicsController
{
public:
	MultiTextureGraphicsController() = default;

	void Update() override {}

	void AddTexture(const std::string& filePath, const int& xOffset = 0, const int& yOffset = 0, const float& parallax = 1.0, const float& scaleFactor = 1.0);
	std::vector<std::shared_ptr<const Texture>> GetCurrentTextures() const override;

private:
	std::vector<std::shared_ptr<const Texture>> _textures; //List of textures that will all be drawn when rendering this GC
};