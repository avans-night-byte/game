#pragma once

// TODO: Remove this
#include "../Engine/Input/Input.hpp"
#include "../Engine/Audio/AudioType.h"

#include <list>
#include <map>
#include "memory"
#include <mutex>

#include "Components/Component.hpp"

#include "Scenes/LevelBase.hpp"


class PhysicsAPI;
class ComponentFactory;
class LevelParserAPI;
class RenderingAPI;

class Game {
private:
    static Game *instance;
    static std::mutex mutex;

private:
    System<Component> components;
    std::list<EntityId> entities;
    std::map<PlayerId, EntityId> players;

    std::unique_ptr<LevelBase> levelBase;

    std::unique_ptr<LevelParserAPI> levelParserAPI;
    std::unique_ptr<ComponentFactory> componentFactory;

protected:
    Game() = default;

    ~Game() = default;

public:
    Game(Game &other) = delete;

    void operator=(const Game &) = delete;

    static Game *getInstance();

public:
    static void initialize();

    static void gameLoop();

    static void debugLog(Input i);

public:
    EntityId createEntity();

    void addComponent(EntityId id, Component *comp);

    template<typename T>
    T *getComponent(EntityId id);

    System<Component> getComponents(EntityId id);

    template<typename T>
    System<T> getComponents(EntityId id);

    PhysicsAPI *getPhysicsAPI();

    RenderingAPI *getRenderingApi();

    static void setCurrentState(int state);

};
