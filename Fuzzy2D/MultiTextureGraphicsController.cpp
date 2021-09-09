#include "MultiTextureGraphicsController.h"

/*
	Description:
		Constructs a new texture given the file path. Pushes it back onto _textures.

	Arguments:
		filePath - where the texture is located
		xOffset - When drawn, the horizontal offset from the origin (Top Left)
		yOffset - When drawn, the vertical offset from the origin (Top Left)
		parallax - Relative speed at which to follow along with the camera scrolling. 1.0 follows along at the same speed
		scaleFactor - How the texture should be scaled when rendering
*/
void MultiTextureGraphicsController::AddTexture(const std::string& filePath, const int& xOffset, const int& yOffset, const float& parallax, const float& scaleFactor)
{
	const std::shared_ptr<Texture> texture(new Texture(filePath, scaleFactor));

	if (texture != nullptr)
	{
		texture->SetOffset(xOffset, yOffset);
		texture->SetParallax(parallax);
		_textures.push_back(texture);
	}
}

/*
	Returns:
		An array of all of the textures in this GC. To be rendered all at the same time each frame.
*/
std::vector<std::shared_ptr<const Texture>> MultiTextureGraphicsController::GetCurrentTextures() const
{
	return _textures;
}