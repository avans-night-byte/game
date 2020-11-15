#pragma once

// TODO: Remove this
#include "../Engine/Input/Input.hpp"
#include "../Engine/Audio/AudioType.h"

#include "Components/Component.hpp"
#include <list>
#include <map>
#include "memory"
#include <SDL_render.h>

#include "../API/Audio/AudioAPI.hpp"
#include "../API/Physics/PhysicsAPI.hpp"

using namespace std;

class Game {
private:
    System<Component> components;
    unique_ptr<PhysicsAPI> physicsAPI;
    SDL_Renderer *sdlRenderer;
    SDL_Window *window;

    std::list<EntityId> entities;
    std::map<PlayerId, EntityId> players;

public:
    static void gameLoop();

    static void debugLog(Input i);

    EntityId createEntity();

    void addComponent(EntityId id, Component *comp);

    template<typename T>
    T *getComponent(EntityId id);

    System<Component> getComponents(EntityId id);

    template<typename T>
    System<T> getComponents(EntityId id);
};