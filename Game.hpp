#pragma once

// TODO: Remove this
#include "../Engine/Input/Input.hpp"
#include "../Engine/Audio/AudioType.h"

#include "../API/Input/EngineInputAPI.hpp"
#include "../Engine/Engine.hpp"
#include "../API/Engine/EngineWindowAPI.hpp"
#include "../API/Audio/EngineAudioAPI.hpp"
#include "../API/XMLParser/MenuParserAPI.hpp"

#include "../API/Input/EngineInputAPI.hpp"
#include "../API/Physics/BodyHandlerAPI.hpp"

#include "./Object/Pool.hpp"
#include "./Components/BulletComponent.hpp"

#include <list>
#include <map>
#include "memory"
#include "CheatMode.hpp"
#include <mutex>

class PhysicsAPI;

class ComponentFactory;

class LevelParserAPI;

class InputAPI;

class RenderingAPI;

class LevelBase;

class PoolLevel;

class Component;

struct LevelData;


class Game {
private:
    static Game *_instance;
    static std::mutex mutex;

private:
    std::unique_ptr<EntityObject> _character;
    System<Component> _components; // TODO: Maybe remove this?

    std::list<EntityId> _entities;

    std::unique_ptr<LevelBase> _levelBase; // TODO: Make a list out of this so we can switch from levels without destroying the other one.
    std::unique_ptr<PoolLevel> _poolLevelBase;

    std::unique_ptr<ComponentFactory> _componentFactory;

    bool _gameLoop = true;
    bool _isCheatMode = false;


    // API's
    std::unique_ptr<InputAPI> _inputAPI;
    std::unique_ptr<WindowAPI> _windowAPI;
    std::unique_ptr<AudioAPI> _audioAPI;
    std::unique_ptr<RenderingAPI> _renderingAPI;
    std::unique_ptr<BodyHandlerAPI> _bodyHandlerAPI;
    std::unique_ptr<PhysicsAPI> _physicsAPI;
    std::unique_ptr<MenuParserAPI> _menuParser;

    std::unique_ptr<CheatMode> _cheatMode;

private:
    void QuitLevel(std::string command);

    void QuitGame(std::string command);

protected:
    Game() = default;

    ~Game() = default;

public:
    Game(Game &other) = delete;

    void operator=(const Game &) = delete;

    static Game *getInstance();

public:
    void initialize();

    void gameLoop();

public:
    inline PoolLevel* getPoolLevel() {
        return _poolLevelBase.get();
    }

    EntityId createEntity();

    void addComponent(EntityId id, Component *comp);

    template<typename T>
    T *getComponent(EntityId id);

    System<Component> getComponents(EntityId id);

    template<typename T>
    System<T> getComponents(EntityId id);

    InputAPI &getInputAPI();

    PhysicsAPI &getPhysicsAPI();

    RenderingAPI &getRenderingApi();

    ComponentFactory *getComponentFactory();

    void initializeLeveL(const std::string &levelName, const LevelData &data);

    void addEventBodyHandler(const std::function<void()> &function);

    void unloadLevel();

    LevelBase& getLevel();

    EntityObject *getCharacter();
    void fixedUpdate(float deltaTime);

    void renderMenu();

};
