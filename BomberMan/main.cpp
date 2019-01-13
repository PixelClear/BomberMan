#include "Game.h"

using namespace Engine;




class Callbacks : public SDLCallbacks
{
public:
    virtual void onInit(SDL_Renderer* renderer)override;
    virtual void onKey(SDL_Renderer* renderer, int keyCode, bool pressed) override;
    virtual void onViewportSizeChanged(SDL_Renderer* renderer,int w, int h) override;
    virtual void onRenderFrame(SDL_Renderer* renderer, double deltaTime) override;
    virtual void onUpdateFrame(SDL_Renderer* renderer, double elapseTime) override;

    Texture texture_;
};


void Callbacks::onInit(SDL_Renderer* renderer)
{
    texture_.loadTexture("../Assets/FlappyBird.png", renderer);
}

void Callbacks::onKey(SDL_Renderer*, int keyCode, bool pressed)
{

}

void Callbacks::onViewportSizeChanged(SDL_Renderer*, int w, int h)
{

}

void Callbacks::onRenderFrame(SDL_Renderer* renderer, double deltaTime)
{
    texture_.RenderTexture(renderer);
}

void Callbacks::onUpdateFrame(SDL_Renderer* renderer, double elapseTime)
{
    static double time = 0;
    time += elapseTime;

    SDL_Rect src;
    src.w = texture_.getWidth();
    src.h = texture_.getHeight();
    src.x = 0;
    src.y = 0;

    SDL_Rect dst;
    dst.w = 64;
    dst.h = 64;
    dst.x = time;
    dst.y = 0;

    texture_.setSrcRect(src);
    texture_.setDstRect(dst);
}

int main(int argc, char* argv[])
{
    try
    {
        Callbacks cb ;
        
        std::unique_ptr<GameEngine> ge = std::make_unique<GameEngine>(&cb, "BomberMan - Reloaded", 800, 600, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, false);
        
        ge->renderMainLoop();
    }
    catch (std::exception e)
    {
        std::cerr << e.what();
    }
    return 0;
}

