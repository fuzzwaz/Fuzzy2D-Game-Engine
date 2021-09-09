#include "UserInterfaceManager.h"
#include "GameObjectRegistryLocator.h"
#include "GameObjectRegistryService.h"
#include "GraphicAssetResources.h"
#include "GraphicObject.h"

using std::shared_ptr;

UserInterfaceManager::UserInterfaceManager() : _centerScreenPosition(Vector2(SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2)))
{

}

void UserInterfaceManager::Notify(const GameObjectEvent& eventType)
{
	if (_eventMap.find(eventType) != _eventMap.end())
	{
		const auto uiElementPrototype = _eventMap.at(eventType);
		const auto uiElement = uiElementPrototype.first->Clone(uiElementPrototype.second);
		GameObjectRegistryLocator::GetCreatorService()->AddGameObjectToScene(uiElement);
	}
}