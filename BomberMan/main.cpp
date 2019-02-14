#include "Game.h"
#include "Components.h"
#include "Collission.h"
#include <fstream>

using namespace Engine;

constexpr uint32_t mapWidth = 10;
constexpr uint32_t mapHeight = 10;

constexpr uint32_t tileWidth = 64;
constexpr uint32_t tileHeight = 64;

EntityComponentManager manager;
Entity& player(manager.addEntity());
Entity& enemey(manager.addEntity());
Entity& gMap(manager.addEntity());

uint32_t map[mapWidth][mapHeight] = { {0, 0, GameObjectType::BrickWall, GameObjectType::BrickWall, 0, 0, 0, 0, 0, 0},
                            {0, 0, GameObjectType::BrickWall, 0, 0, 0, GameObjectType::BrickWall, 0, 0, GameObjectType::WaterBlock},
                            {0, 0, 0, 0, 0, 0, GameObjectType::BrickWall, 0, 0, GameObjectType::WaterBlock},
                            {0, 0, 0, 0, 0, 0, GameObjectType::BrickWall, 0, 0, 0},
                            {0, GameObjectType::GrassBlock, GameObjectType::GrassBlock, 0, 0, 0, 0, 0, GameObjectType::WaterBlock, GameObjectType::WaterBlock},
                            {0, GameObjectType::GrassBlock, 0, 0, 0, 0, 0, 0, 0, GameObjectType::WaterBlock},
                            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            {GameObjectType::BrickWall, GameObjectType::BrickWall, 0, 0, 0, 0, 0, 0, 0, 0},
                            {GameObjectType::BrickWall, GameObjectType::WaterBlock, 0, 0, 0, 0, 0,0, 0, 0},
                            {GameObjectType::WaterBlock, 0, 0, GameObjectType::BrickWall, GameObjectType::BrickWall, 0, 0, 0, GameObjectType::GrassBlock, GameObjectType::GrassBlock} };

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
    ////Load map from file
    //char tile;
    //std::fstream mapFile;
    //mapFile.open("mapfile.map");

    //for (uint32_t i = 0; i < mapWidth; i++)
    //{
    //    for (uint32_t j = 0; j < mapHeight; j++)
    //    {
    //        mapFile.get(tile);
    //        map[i][j] = static_cast<GameObjectType>(tile);
    //        mapFile.ignore(); //ignore , in file
    //    }
    //}

    //mapFile.close();

    for (uint32_t i = 0; i < mapWidth; i++)
    {
        for (uint32_t j = 0; j < mapHeight; j++)
        {
            if (map[i][j] != 0)
            {
                int x = j * tileWidth;
                int y = i * tileHeight;
                gMap.addComponent<TileComponent>(renderer, x, y, tileWidth, tileHeight, static_cast<GameObjectType>(map[i][j]));
                gMap.addComponent<CollisionComponent>("Tile");
            }
        }
    }

    player.addComponent<TransformationComponent>(0, 0, 64, 64, 1);
    player.addComponent<SpriteComponent>(renderer, "../Assets/player.png");
    player.addComponent<InputControllerComponent>();
    player.addComponent<CollisionComponent>("Player");

    enemey.addComponent<TransformationComponent>(0, 512, 64, 64 ,1);
    enemey.addComponent<SpriteComponent>(renderer, "../Assets/enemy.png");
    enemey.addComponent<CollisionComponent>("Enemy");
}

void Callbacks::onKey(SDL_Renderer*, int keyCode, bool pressed)
{

}

void Callbacks::onViewportSizeChanged(SDL_Renderer*, int w, int h)
{

}

void Callbacks::onRenderFrame(SDL_Renderer* renderer, double deltaTime)
{
    manager.render();
}

void Callbacks::onUpdateFrame(SDL_Renderer* renderer, double elapseTime)
{
    manager.refresh();
    manager.update();

    for (const auto& c : GameEngine::colliders_)
    {
        std::string str = player.getComponent<CollisionComponent>().tag();
        if (player.getComponent<CollisionComponent>().tag() != c->tag())
        {
            if (Collission::AABB(player.getComponent<CollisionComponent>(), *c))
            {
                player.getComponent<TransformationComponent>().velocity() * -1;
            }
        }
      
    }
       
    
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

