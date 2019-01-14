#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>
#include <memory>
#include <chrono>
#include <atomic>
#include <string>
#include <exception>
#include <strstream>

namespace Engine
{
    class GameObject
    {
    public:
        virtual void update(SDL_Renderer* renderer, const SDL_Rect& src, const SDL_Rect& dst) = 0;
        virtual void render(SDL_Renderer* renderer) = 0;
    };

    class Sprite : public GameObject
    {
    public:

        Sprite() = delete;
       
        explicit Sprite(SDL_Renderer* renderer, const std::string& fileName)
        {
            SDL_Surface* tmpSurf = IMG_Load(fileName.c_str());
            if (!tmpSurf)
            {
                throw std::runtime_error("Failed to create surface!!");
            }

            texture_ = SDL_CreateTextureFromSurface(renderer, tmpSurf);
            if (!texture_)
            {
                SDL_FreeSurface(tmpSurf);
                throw std::runtime_error("Failed to create texture!!");
            }

            width_ = tmpSurf->w;
            height_ = tmpSurf->h;
            SDL_FreeSurface(tmpSurf);
        }

        ~Sprite()
        {
            SDL_DestroyTexture(texture_);;
        }

        virtual void update(SDL_Renderer* renderer, const SDL_Rect& src, const SDL_Rect& dst) override
        {
            src_.w = getWidth();
            src_.h = getHeight();
            src_.x = src.x;
            src_.y = src.y;

            dst_.w = dst.w;
            dst_.h = dst.h;
            dst_.x = dst.x;
            dst_.y = dst.y;
        }

        virtual void render(SDL_Renderer* renderer) override
        {
            SDL_RenderCopy(renderer, texture_, &src_, &dst_);
        }

    private:
        
        uint32_t getWidth() const noexcept { return width_; }
        uint32_t getHeight() const noexcept { return height_; }

    private:
        SDL_Rect src_;
        SDL_Rect dst_;
        uint32_t width_;
        uint32_t height_;
        SDL_Texture* texture_ = nullptr;
    };

    

    class SDLCallbacks
    {
    public:
        virtual void onInit(SDL_Renderer* renderer) = 0;
        virtual void onKey(SDL_Renderer* renderer, int keyCode, bool pressed) = 0;
        virtual void onViewportSizeChanged(SDL_Renderer* renderer,int w, int h) = 0;
        virtual void onRenderFrame(SDL_Renderer* renderer, double deltaTime) = 0;
        virtual void onUpdateFrame(SDL_Renderer* renderer, double elapseTime) = 0;
    };


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

            cb_->onInit(renderer_); // This will let application load assets 
        }

        ~GameEngine()
        {
            SDL_DestroyWindow(window_);
            SDL_DestroyRenderer(renderer_);
            SDL_Quit();
            std::cout << "SDL done...." << std::endl;
        }

        SDL_Renderer* getRenderer() const noexcept{ return renderer_; }

        void renderMainLoop() noexcept
        {
            const double FPS = 60;
            const double frameDelay = 1000.0 / FPS;
            double elapsedTime = 0.0;

            static auto timeStart_ = std::chrono::time_point_cast<milisec>(std::chrono::high_resolution_clock::now());
           

            while (handleEvent())
            {
                const auto newTimeStamp = std::chrono::time_point_cast<milisec>(std::chrono::high_resolution_clock::now());
                //Time from start of game loop
                const double deltaTime = std::chrono::duration<double>(newTimeStamp - timeStart_).count(); //time_point.count is long long hence doube cast
                
                
                SDL_RenderClear(renderer_);

                cb_->onUpdateFrame(renderer_, deltaTime); 
                cb_->onRenderFrame(renderer_, deltaTime);

                SDL_RenderPresent(renderer_);

                //Time to render this frame
                timeStamp_ = std::chrono::time_point_cast<milisec>(std::chrono::high_resolution_clock::now()); //This is time_point
                elapsedTime = std::chrono::duration<double>(timeStamp_ - newTimeStamp).count();

                //To control rendering to 60 FPS
                if (frameDelay > elapsedTime)
                {
                    SDL_Delay(static_cast<int>(frameDelay - elapsedTime));
                }
            }
        }

    private:

        bool handleEvent() noexcept
        {
            SDL_Event event;

            SDL_PollEvent(&event);

            switch (event.type)
            {
            case SDL_QUIT:
                return false;

            case SDL_KEYDOWN:
            case SDL_KEYUP:

                cb_->onKey(renderer_, event.key.keysym.sym, event.type == SDL_KEYDOWN);
                break;
            case SDL_WINDOWEVENT:

                if (event.window.type == SDL_WINDOWEVENT_SIZE_CHANGED)
                {
                    width_ = event.window.data1;
                    height_ = event.window.data2;

                    cb_->onViewportSizeChanged(renderer_, width_, height_);
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