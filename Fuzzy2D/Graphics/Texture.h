//
//  Texture.h
//  Fuzzy2D
//
//  Created by Ramy Fawaz in 2021
//  Copyright (c) 2021 Ramy Fawaz. All rights reserved.
//

#pragma once

#include "Vector2.h"

#include <memory>
#include <SDL.h>
#include <string>
#include <vector>

struct GraphicAssetInfo;

/*
    Wrapper class for SDL_Texture. Manages a single sprite (pngs).
    Allows for a variety of property customization to render the Texture exactly as needed.
*/
class Texture
{
public:
    Texture(const std::string& filePath, const float& scaleFactor = 1.0);
    virtual ~Texture();

    static void LoadTextures(std::vector<std::shared_ptr<Texture>>& textures, const GraphicAssetInfo& textureInfo);

    /* Getters */
    int GetWidth() const { return _width; }
    int GetHeight() const { return _height; }
    float GetParallax() const { return _parallax; }
    Vector2 GetOffset() const { return _offset; }
    SDL_Point GetRotationOffset() const { return _rotationOffset; }
    SDL_Texture* GetSDLTexture() const { return _sdlTexture; }
    SDL_RendererFlip GetFlipMode() const { return _flipMode; }
    SDL_Rect GetSDLRect() const;

    /* Setters */
    void SetWidth(int w) { _width = w; }
    void SetHeight(int h) { _height = h; }
    void SetParallax(float parallax) { _parallax = parallax; } //Relative speed at which to follow along with the camera scrolling. 1.0 follows along at the same speed
    void SetSDLTexture(SDL_Texture* texture) { _sdlTexture = texture; } //The underlying SDL_Texture being managed
    void SetFlipMode(SDL_RendererFlip flip) { _flipMode = flip; } //The flip orientation of the texture
    void SetOffset(int x, int y); //When drawn, the position offset from the origin (Top Left)
    void SetRotationOffset(int x, int y); //When drawn, the rotational point offset from the origin (center)

private:
    SDL_Texture* _sdlTexture = nullptr; //The underlying SDL_Texture being managed
    SDL_RendererFlip _flipMode = SDL_RendererFlip::SDL_FLIP_NONE; //The flip orientation of the texture
    
    int _width = 0;
    int _height = 0;
    float _scale = 1.0;

    Vector2 _offset; //When drawn, the position offset from the origin (Top Left)
    SDL_Point _rotationOffset; //When drawn, the rotational point offset from the origin (center)
    float _parallax = 1.0; //Relative speed at which to follow along with the camera scrolling. 1.0 follows along at the same speed
};