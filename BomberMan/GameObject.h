#pragma once
#include "SDLCallbacks.h"
#include <string>

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

        explicit Sprite(SDL_Renderer* renderer, const std::string& fileName);

        ~Sprite()
        {
            SDL_DestroyTexture(texture_);
        }

        virtual void update(SDL_Renderer* renderer, const SDL_Rect& src, const SDL_Rect& dst) override;

        virtual void render(SDL_Renderer* renderer) override;

        void setSrcRect(const SDL_Rect& src) { src_ = src; }

        void setDstRect(const SDL_Rect& dst) { dst_ = dst; }

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
}