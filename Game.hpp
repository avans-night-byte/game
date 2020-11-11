#pragma once

// TODO: Remove this
#include "../Engine/Input/Input.hpp"
#include "Components/Component.hpp"
#include <list>
#include <map>
#include <SDL_render.h>
#include "../API/Audio/AudioAPI.hpp"
#include "../Engine/Audio/AudioType.h"

class Game {

private:
    System<Component> components;
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