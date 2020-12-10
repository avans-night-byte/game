#pragma once

// TODO: Remove this
#include "../Engine/Input/Input.hpp"
#include "../Engine/Audio/AudioType.h"

#include <list>
#include <map>
#include "memory"
#include <mutex>

#include "Components/Component.hpp"
#include "Game.hpp"


class PhysicsAPI;

class ComponentFactory;

class LevelParserAPI;

class RenderingAPI;

class CharacterComponent;

class LevelBase;
#include "../API/Input/EngineInputAPI.hpp"

struct LevelData;


class Game {
private:
    std::unique_ptr<CharacterComponent> characterComponent;

    static Game *instance;
    static std::mutex mutex;

    std::string _levelToLoad;

private:
    System<Component> components;
    std::list<EntityId> entities;
    std::map<PlayerId, EntityId> players;

    std::unique_ptr<LevelBase> levelBase;

    std::unique_ptr<ComponentFactory> componentFactory;

    bool unLoadingLevel = false;

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

    inline LevelBase *getLevelBase() {
        return levelBase.get();
    }

public:
    EntityId createEntity();

    void addComponent(EntityId id, Component *comp);

    template<typename T>
    T *getComponent(EntityId id);

    System<Component> getComponents(EntityId id);

    template<typename T>
    System<T> getComponents(EntityId id);

    const EngineInputAPI *getInputAPI();
    PhysicsAPI *getPhysicsAPI();

    RenderingAPI *getRenderingApi();

    ComponentFactory *getComponentFactory();

    void initializeLeveL(const std::string &levelName, const LevelData &data);

    void unloadLevel(const std::string& levelToLoad);
};
