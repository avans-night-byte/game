#pragma once



#include "../Game.hpp"

#include <map>
#include <memory>

enum Type {
    PHYSICSCOMPONENT = 0,
};

class Component;

class ComponentFactory {
private:
    std::map<std::string, std::unique_ptr<Component>> components{};


public:

    ComponentFactory();
};