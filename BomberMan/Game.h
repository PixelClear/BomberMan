#pragma once

#include "SDL.h"
#include <iostream>
#include <memory>
#include <chrono>
#include <atomic>
#include <string>
#include <exception>
#include <strstream>

namespace Engine
{
    class SDLCallbacks
    {
    public:
        virtual void onKey(int keyCode, bool pressed) = 0;
        virtual void onViewportSizeChanged(int w, int h) = 0;
        virtual void onRenderFrame(double deltaTime) = 0;
        virtual void onUpdateFrame(double elapseTime) = 0;
    };


    class GameEngine
    {

    private:

        using milisec = std::chrono::milliseconds;
        using seconds = std::chrono::seconds;

        template<class Clock, class Duration>
        using TimeStamp = std::chrono::time_point<Clock, Duration>;
   
    public:
        GameEngine() = delete;

        GameEngine(SDLCallbacks* cb, std::string title, uint32_t width, uint32_t height, uint32_t xpos = SDL_WINDOWPOS_CENTERED, uint32_t ypos = SDL_WINDOWPOS_CENTERED, bool fullscreen = false):
            cb_(cb), title_(title), width_(width), height_(height), fullscreen_(fullscreen)
        {
            int flags;

            flags = (fullscreen) ? (SDL_WINDOW_FULLSCREEN) : 0;

            if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
            {
                throw std::runtime_error("SDL_Init() failed to initialize!!");
            }

            window_ = SDL_CreateWindow(title.c_str(), xpos, ypos, width, height, flags);

            if (!window_)
            {
                throw std::runtime_error("SDL_CreateWindow() failed to create window!!");
            }

            renderer_ = SDL_CreateRenderer(window_, -1, 0);

            if (!renderer_)
            {
                SDL_DestroyWindow(window_);
                throw std::runtime_error("SDL_CreateRenderer() failed to create renderer!!");
            }

            SDL_SetRenderDrawColor(renderer_, 255, 0, 255, 255);
        }

        ~GameEngine()
        {
            SDL_DestroyWindow(window_);
            SDL_DestroyRenderer(renderer_);
            SDL_Quit();
            std::cout << "SDL done...." << std::endl;
        }

        void renderMainLoop()
        {
            static auto timeStart_ = std::chrono::time_point_cast<milisec>(std::chrono::high_resolution_clock::now());
            timeStamp_ = std::chrono::time_point_cast<milisec>(std::chrono::high_resolution_clock::now()); //This is time_point

            while (handleEvent())
            {
                const auto newTimeStamp = std::chrono::time_point_cast<milisec>(std::chrono::high_resolution_clock::now());
                const double deltaTime = std::chrono::duration<double>(timeStart_ - newTimeStamp).count(); //time_point.count is long long hence doube cast
                const double elapsedTime = std::chrono::duration<double>(timeStamp_ - newTimeStamp).count();
                timeStamp_ = newTimeStamp;
                
                SDL_RenderClear(renderer_);

                cb_->onUpdateFrame(elapsedTime);
                cb_->onRenderFrame(deltaTime);

                SDL_RenderPresent(renderer_);

            }
        }

    private:

        bool handleEvent()
        {
            SDL_Event event;

            SDL_PollEvent(&event);

            switch (event.type)
            {
            case SDL_QUIT:
                return false;

            case SDL_KEYDOWN:
            case SDL_KEYUP:

                cb_->onKey(event.key.keysym.sym, event.type == SDL_KEYDOWN);
                break;
            case SDL_WINDOWEVENT:

                if (event.window.type == SDL_WINDOWEVENT_SIZE_CHANGED)
                {
                    width_ = event.window.data1;
                    height_ = event.window.data2;

                    cb_->onViewportSizeChanged(width_, height_);
                }
                break;
            default:
                break;
            }

            return true;
        }

        SDLCallbacks* cb_;
        SDL_Window* window_ = nullptr;
        SDL_Renderer* renderer_ = nullptr;
        std::string title_ = "Empty";
        uint32_t width_ = 600;
        uint32_t height_ = 400;
        bool fullscreen_ = false;
        TimeStamp<std::chrono::high_resolution_clock, milisec> timeStamp_;

    };
}