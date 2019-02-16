#include "EntityComponentSystem.h"

void Engine::EntityComponentManager::refresh()
{
    for (size_t i = 0; i < maxGroups; i++)
    {
        auto& v(groupEntities_[i]);

        v.erase(
        std::remove_if(std::begin(v), std::end(v),
            [i](Entity* e)
        {
            return !e->isActive() && e->hasGroup(i);
        })
        , std::end(v));
    }

    entities_.erase(std::remove_if(std::begin(entities_), std::end(entities_),
        [](const std::unique_ptr<Entity>& e)
    {
        return !e->isActive();
    }
    ), std::end(entities_));
}

Engine::Entity & Engine::EntityComponentManager::addEntity()
{
    Entity* e = new Entity(*this);
    std::unique_ptr<Entity> ptr{ e };
    entities_.emplace_back(std::move(ptr));
    return *e;
}

void Engine::EntityComponentManager::addToGroup(Entity * e, GroupId id)
{
    groupEntities_[id].emplace_back(e);
}

//template<typename T, typename... TArgs>
//T& Engine::Entity::addComponent(TArgs&& ...mArgs)
//{
//    T* c(new T(std::forward<TArgs>(mArgs)...));
//    c->entity_ = this;
//    std::unique_ptr<Component> ptr{ c };
//    components_.emplace_back(std::move(ptr));
//
//    componentArray_[getComponentTypeId<T>()] = c;
//    componentBitSet_[getComponentTypeId<T>()] = true;
//
//    c->init();
//
//    return *c;
//}
//template<typename T>
//T & Engine::Entity::getComponent() const
//{
//    auto ptr(componentArray_[getComponentTypeId<T>()]);
//    return *static_cast<T*>(ptr);
//}

void Engine::Entity::addGroup(GroupId group)
{
    groupBitSet_[group] = true;
    manager_.addToGroup(this, group);
}
