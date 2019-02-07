#include "GameObject.h"
#include <SDL_image.h>
#include <iostream>
#include <memory>
#include <chrono>
#include <atomic>
#include <string>
#include <exception>
#include <strstream>

Engine::Sprite::Sprite(SDL_Renderer * renderer, const std::string & fileName)
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

void Engine::Sprite::update(SDL_Renderer * renderer, const SDL_Rect & src, const SDL_Rect & dst)
{
    src_.w = src.w;
    src_.h = src.h;
    src_.x = src.x;
    src_.y = src.y;

    dst_.w = dst.w;
    dst_.h = dst.h;
    dst_.x = dst.x;
    dst_.y = dst.y;
}

void Engine::Sprite::render(SDL_Renderer * renderer)
{
    SDL_RenderCopy(renderer, texture_, &src_, &dst_);
}
