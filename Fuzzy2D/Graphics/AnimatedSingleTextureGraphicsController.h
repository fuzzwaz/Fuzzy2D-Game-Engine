//
//  AnimatedSingleTextureGraphicsController.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2021 Ramy Fawaz. All rights reserved.
//

#pragma once

#include "Animator.h"
#include "GraphicsController.h"

struct GraphicAssetInfo;

/*
	Graphics controller for objects that need to display a single texture at a time and support animations.
	It's main purpose is the manage the animator and ask for texture information when rendering time comes.
 */
class AnimatedSingleTextureGraphicsController : public GraphicsController
{
public:
	AnimatedSingleTextureGraphicsController(PropertyController* propertyController);
	AnimatedSingleTextureGraphicsController(PropertyController* propertyController, const GraphicAssetInfo& singleAnimation);
	void operator=(const AnimatedSingleTextureGraphicsController& source);

	void Update() override;
	std::vector<std::shared_ptr<const Texture>> GetCurrentTextures() const override;

	void SetCurrentAnimation(std::shared_ptr<const Animation> animation);
	void SetAnimationFramePercent(const float& percent);

private:
	std::unique_ptr<Animator> _animator = nullptr; //A single animator for the single texture
};
