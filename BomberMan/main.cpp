#include "Game.h"

using namespace Engine;

class Callbacks : public SDLCallbacks
{
    virtual void onKey(int keyCode, bool pressed) override;
    virtual void onViewportSizeChanged(int w, int h) override;
    virtual void onRenderFrame(double deltaTime) override;
    virtual void onUpdateFrame(double elapseTime) override;
};


void Callbacks::onKey(int keyCode, bool pressed)
{

}

void Callbacks::onViewportSizeChanged(int w, int h)
{

}

void Callbacks::onRenderFrame(double deltaTime)
{

}

void Callbacks::onUpdateFrame(double elapseTime)
{

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

