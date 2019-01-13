#include "Game.h"

using namespace Engine;

class Callbacks : public SDLCallbacks
{
public:
    virtual void onKey(int keyCode, bool pressed) override;
    virtual void onViewportSizeChanged(int w, int h) override;
    virtual void onRenderFrame(SDL_Renderer* renderer, double deltaTime) override;
    virtual void onUpdateFrame(SDL_Renderer* renderer, double elapseTime) override;

    Texture texture_;
};


void Callbacks::onKey(int keyCode, bool pressed)
{

}

void Callbacks::onViewportSizeChanged(int w, int h)
{

}

void Callbacks::onRenderFrame(SDL_Renderer* renderer, double deltaTime)
{
    texture_.RenderTexture(renderer);
}

void Callbacks::onUpdateFrame(SDL_Renderer* renderer, double elapseTime)
{
    static int x = 0;
    x += elapseTime;
    texture_.setDstRect(64, 64, x, 0);
}

int main(int argc, char* argv[])
{
    try
    {
        Callbacks cb ;
        
        std::unique_ptr<GameEngine> ge = std::make_unique<GameEngine>(&cb, "BomberMan - Reloaded", 800, 600, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, false);
        cb.texture_.loadTexture("../Assets/FlappyBird.png", ge->getRenderer());
        ge->renderMainLoop();
    }
    catch (std::exception e)
    {
        std::cerr << e.what();
    }
    return 0;
}

