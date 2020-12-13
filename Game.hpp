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

#include <list>
#include <map>
#include "memory"
#include <mutex>

#include "Components/Component.hpp"
#include "Game.hpp"


class PhysicsAPI;

class ComponentFactory;

class LevelParserAPI;

class InputAPI;

class RenderingAPI;

class CharacterComponent;

class LevelBase;


struct LevelData;


class Game {
private:
    std::unique_ptr<CharacterComponent> _characterComponent;

    static Game *_instance;
    static std::mutex mutex;

    std::string _levelToLoad;
    std::unique_ptr<BodyHandlerAPI> _bodyHandlerAPI;

private:
    System<Component> _components;

    std::list<EntityId> _entities;
    std::map<PlayerId, EntityId> _players;

    std::unique_ptr<LevelBase> _levelBase;
    std::unique_ptr<ComponentFactory> _componentFactory;

    bool unLoadingLevel = false;
    bool _gameloop = true;

    std::unique_ptr<Engine> _engine;
    std::unique_ptr<InputAPI> _inputAPI;
    std::unique_ptr<WindowAPI> _windowAPI;
    std::unique_ptr<RenderingAPI> _renderingAPI;
    std::unique_ptr<PhysicsAPI> _physicsAPI;
    std::unique_ptr<MenuParserAPI> _menuParser;

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

    static void debugLog(Input i);

    inline LevelBase *getLevelBase() {
        return _levelBase.get();
    }

public:
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

    void unloadLevel();


};
