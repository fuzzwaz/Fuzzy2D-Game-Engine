#include "AnimatedSingleTextureGraphicsController.h"
#include "GraphicAssetInfo.h"

AnimatedSingleTextureGraphicsController::AnimatedSingleTextureGraphicsController(PropertyController* propertyController)
{
	_animator = std::make_unique<Animator>(propertyController);
}

AnimatedSingleTextureGraphicsController::AnimatedSingleTextureGraphicsController(PropertyController* propertyController, const GraphicAssetInfo& singleAnimation)
{
	_animator = std::make_unique<Animator>(propertyController);
	
	const std::shared_ptr<Animation> anim = std::make_shared<Animation>(singleAnimation);
	SetCurrentAnimation(anim);
	SetRenderingLayer(singleAnimation._RenderingLayer);
}

void AnimatedSingleTextureGraphicsController::operator=(const AnimatedSingleTextureGraphicsController& source)
{
	if (this == &source)
		return;

	*_animator = *source._animator;
	SetIsActive(source.IsActive());
	SetRenderingLayer(source.GetRenderingLayer());
}

void AnimatedSingleTextureGraphicsController::Update()
{
	if (IsActive())
		_animator->Update();
}

/*
	Description:
		Mainly used when rendering a Graphics Controller. Asks the animator for
		the associated frames (textures) that should be displayed at the moment.

	Returns:
		An array of textures that should be rendered. If empty, no textures should be rendered
*/
std::vector<std::shared_ptr<const Texture>> AnimatedSingleTextureGraphicsController::GetCurrentTextures() const
{
	if (_animator->GetCurrentFrame() == nullptr)
		return {};
	else
		return { _animator->GetCurrentFrame() };
}

void AnimatedSingleTextureGraphicsController::SetCurrentAnimation(std::shared_ptr<const Animation> animation)
{
	_animator->SetCurrentAnimation(animation);
}

void AnimatedSingleTextureGraphicsController::SetAnimationFramePercent(const float& percent)
{
	_animator->SetAnimationFramePercent(percent);
}