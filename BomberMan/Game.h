#pragma once

#include "SDLCallbacks.h"
#include <chrono>
#include <string>
#include <vector>

namespace Engine
{
    class CollisionComponent;

    class GameEngine
    {

    private:

        using milisec = std::chrono::milliseconds;
        using seconds = std::chrono::seconds;

        template<class Clock, class Duration>
        using TimeStamp = std::chrono::time_point<Clock, Duration>;
   
    public:

        //I dont want objects to be get default created as I need all this parameters to create window and renderer
        GameEngine() = delete;

        GameEngine(SDLCallbacks* cb, std::string title, uint32_t width, uint32_t height, uint32_t xpos = SDL_WINDOWPOS_CENTERED, uint32_t ypos = SDL_WINDOWPOS_CENTERED, bool fullscreen = false);

        ~GameEngine()
        {
            SDL_DestroyWindow(window_);
            SDL_DestroyRenderer(renderer_);
            SDL_Quit();
        }

        SDL_Renderer* getRenderer() const noexcept{ return renderer_; }

        static SDL_Event getEvent() noexcept { return event_; }
        
        void renderMainLoop() noexcept;

        static std::vector<CollisionComponent*> colliders_;

    private:

        bool handleEvent() noexcept;

        SDLCallbacks* cb_;
        SDL_Window* window_ = nullptr;
        SDL_Renderer* renderer_ = nullptr;
        std::string title_ = "Empty";
        uint32_t width_ = 600;
        uint32_t height_ = 400;
        bool fullscreen_ = false;
        TimeStamp<std::chrono::high_resolution_clock, milisec> timeStamp_;
        static SDL_Event event_;
    };
}