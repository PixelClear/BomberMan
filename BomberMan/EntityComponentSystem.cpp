#include "EntityComponentSystem.h"

void Engine::EntityComponentManager::refresh()
{
    entities_.erase(std::remove_if(std::begin(entities_), std::end(entities_),
        [](const std::unique_ptr<Entity>& e)
    {
        return !e->isActive();
    }
    ), std::end(entities_));
}

Engine::Entity & Engine::EntityComponentManager::addEntity()
{
    Entity* e = new Entity();
    std::unique_ptr<Entity> ptr{ e };
    entities_.emplace_back(std::move(ptr));
    return *e;
}

template<typename T, typename ...TArgs>
inline T & Engine::Entity::addComponent(TArgs && ...mArgs)
{
    T* c(new T(std::forward<TArgs>(mArgs)...));
    c->entity_ = this;
    std::unique_ptr<Component> ptr{ c };
    components_.emplace_back(std::move(ptr));

    componentArray_[getComponentTypeId<T>()] = c;
    componentBitSet_[getComponentTypeId<T>()] = true;

    c->init();

    return *c;
}
template<typename T>
inline T & Engine::Entity::getComponent() const
{
    auto ptr(componentArray_[getComponentTypeId<T>()]);
    return *static_cast<T*>(ptr);
}