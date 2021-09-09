#include "Transform.h"
#include "UIObject.h"

UIObject::UIObject(const Vector2& position)
{
	_Transform = std::make_shared<Transform>();
	_Transform->SetOrigin(position);
	_Transform->_Collider.SetIsActive(false);
}