#pragma once

#include "Level.h"

class DemoLevel : public Level
{
public:
	DemoLevel()
	{
		_transform = std::make_shared<Transform>(Rectangle(0,0,1280,720));
	}

	virtual void LoadLevel() override {}
	virtual bool LevelHasFinished() const override { return false; }

	/* Getters */
	virtual Vector2 GetCameraStart() const override { return Vector2(0, 0); }
	virtual Vector2 GetPlayerStart() const override { return Vector2(0, 0); }
	virtual std::shared_ptr<const Transform> GetTransform() const override { return _transform; }
	virtual std::shared_ptr<const GraphicsController> GetGraphicsController() const override { return nullptr; }
	virtual std::vector<ColliderInterface*> GetLevelColliders() override { return {nullptr}; }

private:
	std::shared_ptr<Transform>  _transform = nullptr;
};