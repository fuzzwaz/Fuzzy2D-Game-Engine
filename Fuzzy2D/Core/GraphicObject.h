//
//  GraphicObject.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2021 Ramy Fawaz. All rights reserved.
//

#pragma once

#include "AnimatedSingleTextureGraphicsController.h"
#include "GameObject.h"
#include "PropertyController.h"

class Texture;
class TimedDestructionController;

//An object meant to represent a single textured game object 
class GraphicObject : public GameObject
{
public:
	GraphicObject(const Vector2& position = Vector2(0,0), const Vector2& direction = Vector2(0, -1));
	GraphicObject(const GraphicAssetInfo& media, const float& deathTime = -1);
	GraphicObject(const GraphicObject& source);
	virtual ~GraphicObject() override;

	virtual std::shared_ptr<GraphicObject> Clone(const Vector2& position, const Vector2& direction = Vector2(0,-1)) const;

	virtual void Update(const Vector2& cameraPosition, const InputState& input) override;

	/* Getters */
	virtual std::shared_ptr<const GraphicsController> GetGraphicsController() const override { return _graphicsController; }
	virtual ColliderInterface* GetCollider() override { return nullptr; }

	/* Setters */
	void SetPosition(const Vector2& position);

protected:
	std::unique_ptr<TimedDestructionController> _destructionController = nullptr;
	std::shared_ptr<AnimatedSingleTextureGraphicsController> _graphicsController = nullptr;
	PropertyController _propertyController;

	Vector2 _originalPosition;
};

void SpawnGraphicObject(const GraphicObject& prototype, const Vector2& position, const Vector2& direction = Vector2(0, -1));