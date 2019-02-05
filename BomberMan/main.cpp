#include "Game.h"
#include "Components.h"
#include "TileMap.h"

using namespace Engine;


TileMap* gMap;
EntityComponentManager manager;

Entity& player(manager.addEntity());

uint32_t map[10][10] = { {0, 0, GamObjectType::BrickWall, GamObjectType::BrickWall, 0, 0, 0, 0, 0, 0},
                            {0, 0, GamObjectType::BrickWall, 0, 0, 0, GamObjectType::BrickWall, 0, 0, GamObjectType::WaterBlock},
                            {0, 0, 0, 0, 0, 0, GamObjectType::BrickWall, 0, 0, GamObjectType::WaterBlock},
                            {0, 0, 0, 0, 0, 0, GamObjectType::BrickWall, 0, 0, 0},
                            {0, GamObjectType::GrassBlock, GamObjectType::GrassBlock, 0, 0, 0, 0, 0, GamObjectType::WaterBlock, GamObjectType::WaterBlock},
                            {0, GamObjectType::GrassBlock, 0, 0, 0, 0, 0, 0, 0, GamObjectType::WaterBlock},
                            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            {GamObjectType::BrickWall, GamObjectType::BrickWall, 0, 0, 0, 0, 0, 0, 0, 0},
                            {GamObjectType::BrickWall, GamObjectType::WaterBlock, 0, 0, 0, 0, 0,0, 0, 0},
                            {GamObjectType::WaterBlock, 0, 0, GamObjectType::BrickWall, GamObjectType::BrickWall, 0, 0, 0, GamObjectType::GrassBlock, GamObjectType::GrassBlock} };

class Callbacks : public SDLCallbacks
{
public:
    virtual void onInit(SDL_Renderer* renderer)override;
    virtual void onKey(SDL_Renderer* renderer, int keyCode, bool pressed) override;
    virtual void onViewportSizeChanged(SDL_Renderer* renderer,int w, int h) override;
    virtual void onRenderFrame(SDL_Renderer* renderer, double deltaTime) override;
    virtual void onUpdateFrame(SDL_Renderer* renderer, double elapseTime) override;
};


void Callbacks::onInit(SDL_Renderer* renderer)
{
    gMap = new TileMap(renderer, 10, 15, 64, 64);
    gMap->loadMap(&map[0][0]);

    player.addComponent<TransformationComponent>();
    player.addComponent<SpriteComponent>(renderer, "../Assets/BrickWall.png");
    player.addComponent<InputControllerComponent>();
}

void Callbacks::onKey(SDL_Renderer*, int keyCode, bool pressed)
{

}

void Callbacks::onViewportSizeChanged(SDL_Renderer*, int w, int h)
{

}

void Callbacks::onRenderFrame(SDL_Renderer* renderer, double deltaTime)
{
    //gMap->render();
    manager.render();
}

void Callbacks::onUpdateFrame(SDL_Renderer* renderer, double elapseTime)
{
    manager.refresh();
    manager.update();
}

int main(int argc, char* argv[])
{
    try
    {
        Callbacks cb ;

        std::unique_ptr<GameEngine> ge = std::make_unique<GameEngine>(&cb, "BomberMan - Reloaded", 640, 640, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, false);
        
        ge->renderMainLoop();
    }
    catch (std::exception e)
    {
        std::cerr << e.what();
    }
    return 0;
}

