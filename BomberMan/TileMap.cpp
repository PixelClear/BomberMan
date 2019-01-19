#include "TileMap.h"

Engine::TileMap::TileMap(SDL_Renderer* renderer, uint32_t mapWidth, uint32_t mapHeight, uint32_t tileWidth , uint32_t tileHeight) :
   renderer_(renderer), mapWidth_(mapWidth), mapHeight_(mapHeight), tileWidth_(tileWidth), tileHeight_(tileHeight)
{
    map_ = new uint32_t*[mapHeight_];
    for (uint32_t i = 0; i < mapHeight_; i++)
    {
        map_[i] = new uint32_t[mapWidth_];
    }

    for (uint32_t i = 0; i < mapHeight_; i++)
    {
        for (uint32_t j = 0; j < mapWidth_; j++)
        {
            map_[i][j] = 0;
        }
    }

    grass_ = std::make_unique<Sprite>(renderer_, "../Assets/Grass.png");
    brick_ = std::make_unique<Sprite>(renderer_, "../Assets/BrickWall.png");
    water_ = std::make_unique<Sprite>(renderer_, "../Assets/Water.png");

    if (!grass_ || !brick_ || !water_)
    {
        throw std::runtime_error("Unable to load assets for tileMap");
    }

    src_.x = src_.y = dst_.x = dst_.y = 0;
    src_.w = dst_.w = tileWidth_;
    src_.h = dst_.h = tileHeight_;

}

Engine::TileMap::~TileMap()
{
    for (uint32_t i = 0; i < mapHeight_; i++)
    {
        delete[] map_[i];
    }

    delete [] map_;

    //No need to free assets as they are unique pointers they will get cleared in Sprite dtor
}

void Engine::TileMap::loadMap(uint32_t* map)
{
    for (uint32_t i = 0; i < mapHeight_; i++)
    {
        for (uint32_t j = 0; j < mapWidth_; j++)
        {
            map_[i][j] = *((map + i * mapWidth_) + j);
        }
    }

#ifdef _DEBUG
    for (uint32_t i = 0; i < mapHeight_; i++)
    {
        for (uint32_t j = 0; j < mapWidth_; j++)
        {
            std::cout << map_[i][j] << " ";
        }

        std::cout << std::endl;
    }
#endif
}

void Engine::TileMap::render()
{
    for (uint32_t i = 0; i < mapHeight_; i++)
    {
        for (uint32_t j = 0; j < mapWidth_; j++)
        {
            const uint32_t gameObjectType = map_[i][j];

            dst_.x = j * tileWidth_;
            dst_.y = i * tileHeight_;

            switch (gameObjectType)
            {
            case GamObjectType::BrickWall :
                brick_->update(renderer_, src_, dst_);
                brick_->render(renderer_);
                break;
            case GamObjectType::GrassBlock:
                grass_->update(renderer_, src_, dst_);
                grass_->render(renderer_);
                break;
            case GamObjectType::WaterBlock:
                water_->update(renderer_, src_, dst_);
                water_->render(renderer_);
                break;
            }
        }
    }
}

