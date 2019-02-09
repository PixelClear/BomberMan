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

        explicit Sprite(SDL_Renderer* renderer, const char* fileName);

        ~Sprite()
        {
            SDL_DestroyTexture(texture_);
        }

        virtual void update(SDL_Renderer* renderer, const SDL_Rect& src, const SDL_Rect& dst) override;

        virtual void render(SDL_Renderer* renderer) override;

        SDL_Rect& getSrcRect() { return src_; }

        SDL_Rect& getDstRect() { return dst_; }

        void setSrcRect(const SDL_Rect& src) { src_ = src; }

        void setDstRect(const SDL_Rect& dst) { dst_ = dst; }

        uint32_t getWidth() const { return width_; }
        uint32_t& getWidth() { return width_; }
        uint32_t getHeight() const { return height_; }
        uint32_t& getHeight() { return height_; }

    private:
        SDL_Rect src_;
        SDL_Rect dst_;
        uint32_t width_;
        uint32_t height_;
        SDL_Texture* texture_ = nullptr;
    };
}