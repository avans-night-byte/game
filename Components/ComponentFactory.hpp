#pragma once


#include "../Game.hpp"


#include <map>
#include <memory>
#include <iostream>

class Component;
namespace LevelResources {
    class component;
}

class ComponentFactory {
private:
    std::map<std::string, std::unique_ptr<Component>> components{};


public:
    ComponentFactory();

    template<class T>
    T* getComponent(EntityId& id) {
        static_assert(std::is_base_of<Component, T>::value, "T should inherit from class Component");

        auto t = T(id);
        std::unique_ptr<Component> &component = components[t.name()];
        T* newComponent = dynamic_cast<T*>(component->Clone(id, nullptr));

        return newComponent;
    }

    Component* getComponent(const EntityId& id, const std::string &name, const LevelResources::component *loadedComponent);
};