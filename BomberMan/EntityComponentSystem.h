#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include "Vector2D.h"

namespace Engine
{
    class Component;
    class Entity;

    using ComponentId = std::size_t;
    //size_t is typedef to some unsigned int or unsigned long or unsinged long long
    //Depending on platform hence it is portable

    inline ComponentId getComponentId()
    {
        static ComponentId id = 0;
        return id++;
    }

    template<typename T> inline 
    ComponentId getComponentTypeId() noexcept
    {
        static ComponentId typeId = getComponentId();
        return typeId;
    }

    //Constexpr may be evaluated at compile time and must be initialized
    constexpr std::size_t maxComponents = 256;

    using ComponentBitSet = std::bitset<maxComponents>;
    using ComponentArray = std::array<Component*, maxComponents>; //std::array doesnt decay to T* as in case of C

    class Component
    {
    public:
        Component()
        {

        }
        Entity* entity_; //owner of the component this just refers to parent so no smart pointer needed

        virtual void init() = 0;
        virtual void update() = 0;
        virtual void render() = 0;

        virtual ~Component(){}
    private:

    };

    class Entity
    {
    public:
        Entity()
        {

        }

        void update()
        {
            for (auto& c : components_)
                c->update();
        }

        void render()
        {
            for (auto& c : components_)
                c->render();
        }

        bool isActive() const { return active_; }

        void destroy() { active_ = false; }

        template<typename T> bool hasComponent() const
        {
            return componentBitSet_[getComponentTypeId<T>()];
        }

        template<typename T, typename... TArgs>
        T& addComponent(TArgs&&... mArgs)
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
        T& getComponent() const
        {
            auto ptr(componentArray_[getComponentTypeId<T>()]);
            return *static_cast<T*>(ptr);
        }

    private:
        bool active_ = true;
        std::vector<std::unique_ptr<Component>> components_; //List of components owned by the entity (owned hence smart pointer unique)
        ComponentArray componentArray_;
        ComponentBitSet componentBitSet_;
    };

    class EntityComponentManager
    {
    public:

        void update()
        {
            for (auto& e : entities_)
                e->update();
        }

        void render()
        {
            for (auto& e : entities_)
                e->render();
        }

        void refresh();

        Entity& addEntity();

    private:
        std::vector<std::unique_ptr<Entity>>entities_;
    };
   
}