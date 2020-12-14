
#include <iostream>

#include "./Game.hpp"

#include "./Components/ComponentFactory.hpp"
#include "./Components/CharacterComponent.hpp"
#include "../Engine/Rendering/TMXLevel.hpp"
#include "Scenes/LevelBase.hpp"
#include "UI/FrameCounter.h"
#include "Helpers/GameTime.h"


typedef signed int int32;

void Game::initialize() {
    GameTime::getInstance();
    Engine::initWindow(1920, 1080);
    ResourceManager &resourceManager = *ResourceManager::instantiate("../../Resources/XML/Definition/Resources.xml");

    _renderingAPI = std::make_unique<EngineRenderingAPI>();
    _inputAPI = std::make_unique<EngineInputAPI>();
    _windowAPI = std::make_unique<EngineWindowAPI>();
    _audioAPI = std::make_unique<EngineAudioAPI>();
    _physicsAPI = std::make_unique<EnginePhysicsAPI>();
    _menuParser = std::make_unique<MenuParserAPI>(*_renderingAPI, _inputAPI->getInputEvent());
    _componentFactory = std::make_unique<ComponentFactory>();
    _bodyHandlerAPI = std::make_unique<BodyHandlerAPI>(*_physicsAPI);

    resourceManager.loadResource("MainMenu");

    auto characterId = createEntity();
    _characterComponent = std::make_unique<CharacterComponent>(characterId, Vector2(100, 100));
    addComponent(characterId, _characterComponent.get());

    _menuParser->getCustomEventHandler() += std::bind(&Game::QuitLevel, this, std::placeholders::_1);
    _menuParser->getCustomEventHandler() += std::bind(&Game::QuitGame, this, std::placeholders::_1);
}

/**
 * Gameloop
 **/
void Game::gameLoop() {
    bool isDebuggingPhysics = false;

    auto *resourceManager = ResourceManager::getInstance();
    FrameCounter fpsCounter{*_renderingAPI};

    GameTime &time = GameTime::getInstance();
    time.getFixedUpdateEvent() += std::bind(&Game::FixedUpdate, this, std::placeholders::_1);

    // Create texture once
    _renderingAPI->createText("../../Resources/Fonts/LiberationMono-Regular.ttf", "0", 25,
                              "ffffff", "fpsText");
    // Gameloop
    while (_gameLoop) {
        time.update();

        // Poll input and keep track of lastInput
        Input i = _inputAPI->getInput();

        if (i.keyMap.action == "QUIT") {
            Game::QuitGame("close");
            break;
        }

        if (resourceManager->inMenu) {
            _menuParser->render();
        } else if (_levelBase) {
            _levelBase->render();
            _levelBase->update(i);
        }

        fpsCounter.render();
        if (isDebuggingPhysics)
            _physicsAPI->DebugDraw(*_renderingAPI, *_windowAPI->getRenderer());

        _renderingAPI->render();

        if (i.keyMap.code == "]") {
            isDebuggingPhysics = true;
        } else if (i.keyMap.code == "\\") {
            isDebuggingPhysics = false;
        }

        _bodyHandlerAPI->update();
    }
}

void Game::FixedUpdate(float deltaTime){
    if (!ResourceManager::getInstance()->inMenu) {
        _physicsAPI->update(deltaTime);
        if (_levelBase)
            _levelBase->fixedUpdate(deltaTime);
    }
}

void Game::QuitLevel(std::string command) {
    if (command != "unloadLevel") return;
    ResourceManager::getInstance()->quitLevel = true;
}

void Game::QuitGame(std::string command) {
    if (command != "close") return;
    _gameLoop = false;
    _windowAPI->closeWindow();
}

/*
 * The following section managers components in the program, this is not a completed system but you could already use
 * it with your feature, just mage sure to check because some components are not completely done.
 */

/**
 * Creates an entity and pushes it to the entity collection.
 *
 * @return EntityId id - The id of the newly created entity.
 */
EntityId Game::createEntity() {
    auto it = _entities.begin();
    std::advance(it, _entities.size());
    EntityId next = (*it) + 1;
    _entities.push_back(next);

    return next;
}

/**
 * Add a component to the specified entity.
 * @param id
 * @param comp
 */
void Game::addComponent(EntityId id, Component *comp) {
    _components.components.insert(std::pair<EntityId, Component *>(id, comp));
}

template<typename T>

/**
 * Gets a single component of specified type.
 * @tparam T
 * @param id
 * @return
 */
T *Game::getComponent(EntityId id) {
    for (auto &component : _components.components) {
        if ((component.first == id) && dynamic_cast<const T *>(component.second) != nullptr) {
            return (T *) component.second;
        }
    }

    return nullptr;
}

/**
 * Gets components by entity id of all types.
 * @param id
 * @return
 */
System<Component> Game::getComponents(EntityId id) {
    System<Component> returnComps;

    for (auto &component : _components.components) {
        if (component.first == id) {
            returnComps.components.insert(std::pair<EntityId, Component *>(id, component.second));
        }
    }

    return returnComps;
}

/**
 * Gets components by entity id of a specified type.
 * @tparam T
 * @param id
 * @return
 */
template<typename T>
System<T> Game::getComponents(EntityId id) {
    System<Component> returnComps;

    for (auto &it : _components.components) {
        T *component = dynamic_cast<const T *>(it.second);
        if (it.first == id && component != nullptr) {
            returnComps.components.insert(std::pair<EntityId, T *>(id, component));
        }
    }

    return returnComps;
}

/**
 * Static methods should be defined outside the class.
 */
Game *Game::_instance{};
std::mutex Game::mutex;

/**
 * The first time we call getInstance we will lock the storage location
 *      and then we make sure again that the variable is null and then we
 *      set the value.
 */
Game *Game::getInstance() {
    std::lock_guard<std::mutex> lock(mutex);
    if (_instance == nullptr) {
        _instance = new Game();
    }

    return _instance;
}

PhysicsAPI &Game::getPhysicsAPI() {
    return *_physicsAPI;
}

RenderingAPI &Game::getRenderingApi() {
    return *_renderingAPI;
}

ComponentFactory *Game::getComponentFactory() {
    return _componentFactory.get();
}

void Game::initializeLeveL(const std::string &levelName, const LevelData &data) {
    if (_levelBase) {
        unloadLevel();
    }

    (*_bodyHandlerAPI).eventOnBodiesHandled([this, levelName, data] {
        _levelBase = std::make_unique<LevelBase>();
        _levelBase->_characterComponent = this->_characterComponent.get(); // TODO: Character data should be stored in a static class
        _levelBase->initialize(levelName, data);
    });
}

void Game::unloadLevel() {
    if (!_levelBase)
        return;

    (*_bodyHandlerAPI).eventOnWorldLocked([this] {
        _levelBase->destroyAllBodies();
        _levelBase->clearEntities();
        _levelBase = nullptr;
    });
}

InputAPI &Game::getInputAPI() {
    return *_inputAPI;
}
