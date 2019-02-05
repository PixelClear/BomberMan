#pragma once

#include "SDLCallbacks.h"
#include "Components.h"
#include "TileMap.h"
#include "EntityComponentSystem.h"
#include <iostream>
#include <memory>
#include <chrono>
#include <atomic>
#include <string>
#include <exception>
#include <strstream>

namespace Engine
{
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
            std::cout << "SDL done...." << std::endl;
        }

        SDL_Renderer* getRenderer() const noexcept{ return renderer_; }

        static SDL_Event getEvent() noexcept { return event_; }
        
        void renderMainLoop() noexcept;

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
    public:
        static SDL_Event event_;
    };

    SDL_Event GameEngine::event_;
}