#include "GraphicObject.h"
#include "GameObjectRegistryLocator.h"
#include "GameObjectRegistryService.h"
#include "TimedDestructionController.h"
#include "Transform.h"

GraphicObject::GraphicObject(const Vector2& position, const Vector2& direction) : GameObject(position, direction)
{
	_originalPosition = position;
	_destructionController = std::make_unique<TimedDestructionController>(_observerController);
	_graphicsController = std::make_shared<AnimatedSingleTextureGraphicsController>(&_propertyController);
	_graphicsController->SetIsActive(false);
	SetIsActive(false);
}

GraphicObject::GraphicObject(const GraphicAssetInfo& media, const float& deathTime) : GameObject()
{
	_graphicsController = std::make_shared<AnimatedSingleTextureGraphicsController>(&_propertyController, media);
	_destructionController = std::make_unique<TimedDestructionController>(_observerController, deathTime);
	SetIsActive(false);
}

GraphicObject::GraphicObject(const GraphicObject& source) : GameObject(source)
{
	_destructionController = std::make_unique<TimedDestructionController>(_observerController);
	_graphicsController = std::make_shared<AnimatedSingleTextureGraphicsController>(&_propertyController);

	*_graphicsController = *source._graphicsController;
	*_destructionController = *source._destructionController;
	_originalPosition = source._originalPosition;
}

GraphicObject::~GraphicObject()
{
	_graphicsController.reset();
	_destructionController.reset();
}

/*
	Description:
		Creates a new active copy of the GraphicObject which shares the same animator from the original. This avoids
		the re-initialization of the textures and animations associated with a graphic object.

	Arguments:
		position - The initial position for the cloned GraphicObject in world coordinates
		direction - Where the clone is facing. Defaults to up (0, -1)
*/
std::shared_ptr<GraphicObject> GraphicObject::Clone(const Vector2& position, const Vector2& direction) const
{
	std::shared_ptr<GraphicObject> clone = std::make_shared<GraphicObject>(position, direction);
	clone->SetPosition(position);
	*clone->_graphicsController = *_graphicsController;
	*clone->_destructionController = *_destructionController;

	clone->SetIsActive(true);
	return clone;
}

void GraphicObject::SetPosition(const Vector2& position)
{
	_transform->SetOrigin(position);
	_originalPosition = position;
}

void GraphicObject::Update(const Vector2& cameraPosition, const InputState& input)
{
	if (_destructionController->TimeIsUp())
		return;

	//Graphic Objects on the UI Rendering Layer should always adjust to the camera's current position for the upcoming view transformation to camera space 
	if (_graphicsController->GetRenderingLayer() == RenderingLayer::UI)
		_transform->SetOrigin(_originalPosition + cameraPosition);

	_graphicsController->Update();
}

void SpawnGraphicObject(const GraphicObject& prototype, const Vector2& position, const Vector2& direction)
{
	const std::shared_ptr<GraphicObject> clone = prototype.Clone(position, direction);
	GameObjectRegistryLocator::GetCreatorService()->AddGameObjectToScene(clone);
}