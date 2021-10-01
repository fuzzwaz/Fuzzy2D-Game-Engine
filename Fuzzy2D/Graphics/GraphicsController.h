//
//  GraphicsController.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2021 Ramy Fawaz. All rights reserved.
//

#pragma once

#include "Common.h"
#include "Texture.h"

#include <memory>
#include <vector>

/*
	An interface meant to manage the graphical elements for any object in the scene.
	Objects communicate through their GraphicsController so that they don't need to deal with low level animation code.
 */
class GraphicsController
{
public:
	virtual void Update() = 0; //How GraphicsControllers progress their graphics over the course of the game (for instance, telling the animator to update frames)
	virtual std::vector<std::shared_ptr<const Texture>> GetCurrentTextures() const = 0; //Returns the textures that the renderer needs to draw

	virtual bool IsActive() const { return _isActive; } //Whether or not the GC should be rendered
	virtual void SetIsActive(const bool& active) { _isActive = active; }

	RenderingLayer GetRenderingLayer() const { return _renderingLayer; } //What order to draw this GC compared to others
	void SetRenderingLayer(const RenderingLayer& layer) { _renderingLayer = layer; }

private:
	bool _isActive = true; //Whether or not the GC should be rendered
	RenderingLayer _renderingLayer = RenderingLayer::GENERAL; //What order to draw this GC compared to others
};