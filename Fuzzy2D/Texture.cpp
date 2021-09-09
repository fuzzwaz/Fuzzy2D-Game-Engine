#include "GraphicAssetInfo.h"
#include "Renderer.h"
#include "Texture.h"


Texture::Texture(const std::string& filePath, const float& scaleFactor)
{
    //The Renderer acts as a wrapper for the SDL_Renderer which is needed of making SDL_Textures
    Renderer::CreateTextureFromFile(*this, filePath);
    _scale = scaleFactor;
}

Texture::~Texture()
{
    if (_sdlTexture != nullptr)
    {
        SDL_DestroyTexture(_sdlTexture);
        _sdlTexture = nullptr;
    }
}

/*
    Description:
        A static function used to create an list of Textures all at once (typically all of the textures within an Animation.
        Requires that textures are .png files.
        Requires that textures files utilize the same naming convention ("fileName_01" , "fileName_02", ...)

    Arguments:
		textures - Pass by Ref vector of textures. Will be populated with textures defined in textureInfo.
		textureInfo - A struct filled with information about the textures that needed to be created. Including file path, file count, and texture size.

	Return:
		std::vector<std::shared_ptr<Texture>>& - Pass by Ref textures is updated
*/

void Texture::LoadTextures(std::vector<std::shared_ptr<Texture>>& textures, const GraphicAssetInfo& textureInfo)
{
    const std::string EXT = ".png";

    for (int i = 0; i < textureInfo._TextureCount; i++)
    {
        const std::shared_ptr<Texture> texture = std::make_shared<Texture>(textureInfo._FilePath + std::to_string(i) + EXT, textureInfo._TextureScale);

        const Vector2 size = Vector2(texture->GetWidth(), texture->GetHeight()) * textureInfo._TextureScale;
        texture->SetOffset(size.x * textureInfo._TextureOffset.x, size.y * textureInfo._TextureOffset.y);
        texture->SetRotationOffset(size.x * textureInfo._TextureRotationOffset.x, size.y * textureInfo._TextureRotationOffset.y);

        textures.push_back(texture);
    } 
}

/*
    Description:
        SDL_Rects are needed to identify the bounds of an SDL_Texture when drawing with the SDL_Renderer.
        It's model space so the x & y coordinates are 0. However, we adjust the width & height to match the specified
        scale factor.

    Return:
		SDL_Rect - The bounds in which the texture will be stretched or cropped to fit within while rendering
*/
SDL_Rect Texture::GetSDLRect() const
{
    SDL_Rect textureRect;
    textureRect.x = 0;
    textureRect.y = 0;
    textureRect.w = _width * _scale;
    textureRect.h = _height * _scale;
    return textureRect;
}

void Texture::SetOffset(int x, int y)
{
    _offset.x = x;
    _offset.y = y;
}

void Texture::SetRotationOffset(int x, int y)
{
    _rotationOffset.x = x;
    _rotationOffset.y = y;
}
