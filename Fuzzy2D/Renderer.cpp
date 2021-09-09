#include "Common.h"
#include "ErrorHandler.h"
#include "GraphicsController.h"
#include "Renderer.h"
#include "StringResources.h"
#include "Transform.h"

#include <SDL_events.h>
#include <SDL_image.h>
#include <SDL_render.h>

SDL_Renderer* Renderer::SDL_RENDERER = nullptr;

Renderer::Renderer(std::shared_ptr<const ScrollingCamera> camera)
{
    _camera = camera;
    ErrorHandler::Assert(Initialize(), "Renderer failed to initialize"); //Sets up the SDL specific rendering and graphics code

}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(SDL_RENDERER);
    SDL_DestroyWindow(sdlWindow);

    SDL_RENDERER = nullptr;
    sdlWindow = nullptr;

    IMG_Quit();
}

/*
    Description:
        Creates and SDL_Window and SDL_Renderer in which this class acts as a Wrapper for.
        Required to draw to the screen using SDL's APIs.
        Required to create SDL_Textures.

    Return:
        bool - Whether or not the Renderer initialization was successful. If false, nothing will render to the screen
*/
bool Renderer::Initialize()
{
    bool successfulInitialization = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) //Needed to setup the entire graphics system
        successfulInitialization = false;
    else
    {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0")) //Controls pixel scaling quality. "0" is ideal for pixel art clarity
            successfulInitialization =  false;
        else
        {
            /*                           Name displayed on top of Window,      x Position          ,       y Position         ,     Width     ,     Height     ,  Visible by default*/
            sdlWindow = SDL_CreateWindow(Resources::Strings::WINDOW_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
            if (sdlWindow == nullptr)
                successfulInitialization =  false;
            else
            {

                //SDL_SetWindowFullscreen(sdlWindow, 1);
                //SDL_ShowCursor(0); //Hide OS cursor in favor of our own custom cursor

                SDL_RENDERER = SDL_CreateRenderer(sdlWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
                if (SDL_RENDERER == nullptr)
                    successfulInitialization =  false;
                else
                {
                    if (!IMG_Init(IMG_INIT_PNG)) //Initializating the image libraries that are used for PNGs specifically
                        successfulInitialization = false;
                }
            }
        }
    }

    ClearScreen();
    SwapFrameBuffers();
    return successfulInitialization;
}

/*
    Description:
        Coordinate space transformation from Model to Camera space

    Arguments:
        point - A point in Model space
        origin - An relative origin in World Space

    Return:
		Vector2 - The original point defined in Camera space coordinates
*/
Vector2 Renderer::ConvertPointFromModelToCameraSpace(const Vector2 point, const Vector2 origin) const
{
    //Model to World
    Vector2 adjustedPoint = point;
    adjustedPoint.x += origin.x;
    adjustedPoint.y += origin.y;

    //World to Camera
    const Vector2 camerPos = _camera->GetPosition();
    adjustedPoint.x -= camerPos.x;
    adjustedPoint.y -= camerPos.y;

    return adjustedPoint;
}

/*
    Description:
        Calculates the final Texture camera position after applying all applicable offsets
        and converting coordinate spaces.

    Arguments:
        texture - The texture we are calculating the origin for
        worldSpacePosition - It's current position in world space
        additionalOffset - Any additional offset that may need to be applied onto the texture's position. Defaults to (0,0)

    Return:
        Vector2 - The texture's Camera Space position. Ready for rendering
*/
Vector2 Renderer::CalculateCameraCoordinatesForTexture(const std::shared_ptr<const Texture>& texture, const Vector2& worldSpacePosition, const Vector2& additionalOffset) const
{
    Vector2 texturePosition = worldSpacePosition;
    texturePosition = texturePosition + texture->GetOffset(); //Factor in the position offset unique to the texture itself
    texturePosition = texturePosition + additionalOffset; //Any addition drawing offsets. Possibly due to screen effects like screen shake

    const Vector2 parallaxedCameraPosition = _camera->GetPosition() * texture->GetParallax(); //The the camera's parallaxed position in world space
    texturePosition = texturePosition - parallaxedCameraPosition; //World -> Camera coordinate transform

    return texturePosition;
}

/*
    Description:
        Renders a set of red lines for debugging purposes.

    Arguments:
        points - A vector of model space point positions which represent line end points.
        origin - The origin position in world space
*/
void Renderer::Render(const std::vector<Vector2>& points, const Vector2& origin)
{
    SDL_SetRenderDrawColor(SDL_RENDERER, 0xFF, 0x00, 0x00, 0xFF); //Draw in Red
    for (int i = 0; i < points.size(); i++)
    {
        //Draw the single point
        const Vector2 position = ConvertPointFromModelToCameraSpace(points.at(i), origin);
        SDL_RenderDrawPoint(SDL_RENDERER, position.x, position.y);

        //Check to see if there is a point afterwards, if so, draw a line between the two points
        if (i + 1 < points.size())
        {
            const Vector2 nextPosition = ConvertPointFromModelToCameraSpace(points.at(i + 1), origin);
            SDL_RenderDrawLine(SDL_RENDERER, position.x, position.y, nextPosition.x, nextPosition.y);
        }
    }

    //Finish by drawing the last line from the last point to the initial point
    if (points.size() > 1)
    {
        const Vector2 position = ConvertPointFromModelToCameraSpace(points.at(points.size() - 1), origin);
        const Vector2 nextPosition = ConvertPointFromModelToCameraSpace(points.at(0), origin);
        SDL_RenderDrawLine(SDL_RENDERER, position.x, position.y, nextPosition.x, nextPosition.y);
    }
}

/*
    Description:
        Renders all of the current textures stored in a Graphics Controller given a specific
        World coordinate position.

    Arguments:
        transform - The transform associated with the GC. Tells us the World coordinate position
        graphicsController - Houses all of the textures being rendered and helpful info about how to render those textures

    Return:
        Vector2 - The texture's Camera Space position. Ready for rendering
*/
void Renderer::Render(const std::shared_ptr<const Transform>& transform, const std::shared_ptr<const GraphicsController>& graphicsController)
{
    //Updates _renderingEffectOffset to match the current effect offset for the given layer
    UpdateRenderingEffectOffset(graphicsController->GetRenderingLayer());

    for (const std::shared_ptr<const Texture>& texture : graphicsController->GetCurrentTextures())
    {
        RenderTexture(*(transform.get()), texture);
    }
}

/*
    Description:
        Renders a single texture the SDL way. The function converts how texture info to match
        what is expected by the SDL renderer. 

    Arguments:
        transform - The transform associated with the GC. Tells us the World coordinate position
        texture - The texture being drawn
*/
void Renderer::RenderTexture(const Transform& transform, const std::shared_ptr<const Texture>& texture) const
{
    if (texture == nullptr)
        return;

    const SDL_Point rotationCenter = texture->GetRotationOffset(); //The model space point where the texture is rotated 
    const Vector2 texturePosition = CalculateCameraCoordinatesForTexture(texture, transform.GetOrigin(), _renderingEffectOffset);
    const SDL_Rect sourceRect = texture->GetSDLRect(); //The model space bounding rect
    SDL_Rect destinationRect = sourceRect; //The camera space bounding rect

    destinationRect.x = texturePosition.x;
    destinationRect.y = texturePosition.y;

    //SDL rendering call
    SDL_RenderCopyEx(SDL_RENDERER, texture->GetSDLTexture(), &sourceRect, &destinationRect, transform.GetOrientationAngle(), &rotationCenter, texture->GetFlipMode());
}


void Renderer::ClearScreen()
{
    SDL_SetRenderDrawColor(SDL_RENDERER, 0, 0, 0, 255);
    SDL_RenderClear(SDL_RENDERER);
}

void Renderer::SwapFrameBuffers()
{
    SDL_RenderPresent(SDL_RENDERER);
}

/*
    Description:
        Rendering effects can cause movement or scaling changes to a texture. This function
        updates the internal properties which get applied to textures to showcase the effects.

        Currently, only screen shake is supported. 

    Arguments:
        renderingLayer - The Layer which is about to be rendered. Some effects are only applied to some layers.
						 For example, screen shake is not applied to the UI layer.
*/
void Renderer::UpdateRenderingEffectOffset(const RenderingLayer& renderingLayer)
{
    //Screen Shake is not applied to the UI Layer
    if (!_screenShake || renderingLayer == RenderingLayer::UI)
        _renderingEffectOffset = Vector2(0, 0);
    else
        _renderingEffectOffset = CommonHelpers::RandomOffset(_screenShakeMagnitude);
}

/*
    Description:
        Multiple callers can initiate a screen shake effect. This function
        ensures that screen shake remains active when until all callers have
        deactivated their screen shake requests

    Arguments:
        active - A request to activate or deactivate screen shake. 
*/
void Renderer::SetScreenShake(const bool active)
{
    if (active)
        _shakeActiveCount++;
    else if (_shakeActiveCount > 0)
        _shakeActiveCount--;

    //As long as there's at least one caller which requires screen shake, keep the effect on
    _screenShake = _shakeActiveCount > 0;
}

/*
    Description:
        Creates a SDL_Texture for the given filePath and sets it up properly in the
        given Texture wrapper.

    Arguments:
        newTexture - The empty Texture wrapper which will become the new home for the constructed SDL_Texture
        filePath - The filePath for a png that will encoded into an SDL_Texture

    Output:
		Texture& - Updated Texture object that holds an SDL_Texture representation of the file at filePath
*/
bool Renderer::CreateTextureFromFile(Texture& newTexture, const std::string& filePath)
{
    SDL_Texture* sdlTexture = nullptr;
    SDL_Surface* loadedSurface = IMG_Load(filePath.c_str());

    ErrorHandler::Assert(loadedSurface != nullptr, "Unable to load image from: " + filePath + ". SDL_image Error: " + IMG_GetError());
    
    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
    sdlTexture = SDL_CreateTextureFromSurface(SDL_RENDERER, loadedSurface);

    ErrorHandler::Assert(sdlTexture != nullptr, "Unable to create texture from: " + filePath + ". SDL Error: " + SDL_GetError());
    newTexture.SetWidth(loadedSurface->w);
    newTexture.SetHeight(loadedSurface->h);

    SDL_FreeSurface(loadedSurface);

    newTexture.SetSDLTexture(sdlTexture);
    return sdlTexture != nullptr;
}