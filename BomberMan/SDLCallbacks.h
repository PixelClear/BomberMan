#pragma once
#include "SDL.h"
#include "SDL_image.h"
namespace Engine
{
    class SDLCallbacks
    {
    public:
        virtual void onInit(SDL_Renderer* renderer) = 0;
        virtual void onKey(SDL_Renderer* renderer, int keyCode, bool pressed) = 0;
        virtual void onViewportSizeChanged(SDL_Renderer* renderer, int w, int h) = 0;
        virtual void onRenderFrame(SDL_Renderer* renderer, double deltaTime) = 0;
        virtual void onUpdateFrame(SDL_Renderer* renderer, double elapseTime) = 0;
    };

}
