#pragma once

// TODO: Remove this
#include "../Engine/Input/Input.hpp"
#include "../Engine/Audio/AudioType.h"

#include <list>
#include <map>
#include "memory"
#include <mutex>

#include "../API/Audio/AudioAPI.hpp"
#include "../API/Physics/PhysicsAPI.hpp"

#include "Components/Component.hpp"
class CharacterComponent;
using namespace std;

class Game {
private:
    static Game *instance;
    static std::mutex mutex;
    unique_ptr<CharacterComponent> characterComponent;

private:
    System<Component> components;
    std::list<EntityId> entities;
    std::map<PlayerId, EntityId> players;

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

    const PhysicsAPI *getPhysicsAPI();

    static void setCurrentState(int state);

    void resetGame();

    void startGame();

    void removeEntity(EntityId &id);

    void removeComponents(EntityId &id);
};