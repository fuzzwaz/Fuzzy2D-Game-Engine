#include "Rectangle.h"

bool Rectangle::operator==(const Rectangle& other) const
{
	return this->_Origin == other._Origin &&
		this->_Width == other._Width &&
		this->_Height == other._Height;
}

Vector2 Rectangle::Center() const
{
	Vector2 c(_Origin.x + (_Width / 2.0), _Origin.y + (_Height / 2.0));
	return c;
}