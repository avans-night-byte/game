#pragma once


#include "../Game.hpp"

#include <map>
#include <memory>

class Component;

class ComponentFactory {
private:
    std::map<std::string, std::unique_ptr<Component>> components{};


public:
    ComponentFactory();

    template<class T>
    T* getComponent(EntityId id) {
        static_assert(std::is_base_of<Component, T>::value, "T should inherit from class Component");

        auto t = T(id);
        std::unique_ptr<Component> &component = components[t.name()];
        T* newComponent = dynamic_cast<T*>(component->Clone(id));

        return newComponent;
    }

    Component* getComponent(EntityId id, const std::string &name) {
        std::unique_ptr<Component> &component = components[name];

        if(component == nullptr)
        {
            std::cout << "Couldn't find " + name << std::endl;
        }

        return component->Clone(id);
    }
};