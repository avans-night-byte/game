
#include <iostream>

#include "./Game.hpp"


// Fixme: No hardie
#include "./Scenes/Menu/MainMenu.cpp"
#include "./Scenes/Example/ExampleScene.hpp"
#include "./Scenes/Credits/Credits.hpp"
#include "./Scenes/Level1/Level1.hpp"
#include "./Scenes/Level10/LevelCharlie.hpp"

#include "../API/XMLParser/LevelParserAPI.hpp"
#include "../API/Input/EngineInputAPI.hpp"
#include "../API/XMLParser/MenuParserAPI.hpp"
#include "../API/Physics/EnginePhysicsAPI.hpp"

#include "./Components/ComponentFactory.hpp"
#include "./Components/CharacterComponent.hpp"
#include "../Engine/Rendering/TMXLevel.hpp"
#include "../Engine/Managers/ResourceManager.hpp"

typedef signed int int32;

const int width = 1920;
const int height = 1080;

Engine *engine;
EngineInputAPI *engineInputAPI;
EngineWindowAPI *engineWindowAPI;
RenderingAPI *renderingAPI; // TODO:  EngineRenderingAPI -> RenderinAPI: Change this since we are using the interface instance.
PhysicsAPI *physicsAPI;
AudioAPI *audioApi;
MenuParserAPI *menuParser;


void Game::initialize() {
    // Load in all resources
    ResourceManager resourceManager = ResourceManager("../../Resources/XML/Definition/Resources.xml");

    Engine::initWindow(width, height);
    renderingAPI = new EngineRenderingAPI();
    engineInputAPI = new EngineInputAPI();
    engineWindowAPI = new EngineWindowAPI(engine);
    audioApi = new AudioAPI();
    physicsAPI = new EnginePhysicsAPI();
    menuParser = new MenuParserAPI(*renderingAPI, engineInputAPI->getInputEvent());


    Game *game = Game::getInstance();
    game->componentFactory = make_unique<ComponentFactory>();

    menuParser->loadScene("../../Resources/XML/Definition/MainMenu.xml");

    // We should normally init when switching state.
    Credits::init(renderingAPI, engineWindowAPI, audioApi);

    const TMXLevelData levelData = TMXLevelData("../../Resources/example.tmx",
                                                "../../Resources/Sprites/Overworld.png",
                                                "Overworld");

    game->levelParserAPI = std::make_unique<LevelParserAPI>();
    game->levelParserAPI->LoadLevel(levelData, "../../Resources/XML/Definition/Level1Resources.xml");
}

/**
 * Gameloop
 **/
void Game::gameLoop() {

    // TODO: Please put this into the class after making gameloop static.
    Game *game = getInstance();

    /** CREATE CHARACTER */
    unique_ptr<CharacterComponent> characterComponent;
    EntityId characterEntityId;

    characterEntityId = game->createEntity();
    characterComponent = make_unique<CharacterComponent>(characterEntityId, Vector2(100, 100));

    game->addComponent(characterEntityId, characterComponent.get());


    bool isDebuggingPhysics = false;

    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    float t = 0.0f;
    double dt = 1 / 60.0;

    auto currentTime = std::chrono::high_resolution_clock::now();
    float accumulator = 0.0;

    // Gameloop
    while (true) {
        // Poll input and keep track of lastInput
        Input i = engineInputAPI->getInput();


        /**  PHYSICS      */
        auto newTime = std::chrono::high_resolution_clock::now();

        // Gets the time in microseconds and converts them into seconds.
        float frameTime =
                std::chrono::duration_cast<std::chrono::microseconds>(newTime - currentTime).count() / 100000.0f;

        currentTime = newTime;
        accumulator += frameTime;

        while (accumulator >= dt) {
            physicsAPI->update(dt, velocityIterations, positionIterations);

            t += dt;
            accumulator -= dt;
        }

        menuParser->render();


        if (isDebuggingPhysics)
            physicsAPI->DebugDraw(*renderingAPI, *engineWindowAPI->getRenderer());

        SDL_RenderPresent(engineWindowAPI->getRenderer());
        SDL_RenderClear(engineWindowAPI->getRenderer());


        if (i.keyMap.action == "QUIT") {
            engineWindowAPI->closeWindow();
            break;
        }

        if (i.keyMap.code == "]") {
            isDebuggingPhysics = true;
        } else if (i.keyMap.code == "\\") {
            isDebuggingPhysics = false;
        }
    }
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
    auto it = entities.begin();
    std::advance(it, entities.size());
    EntityId next = (*it) + 1;
    entities.push_back(next);

    return next;
}

/**
 * Add a component to the specified entity.
 * @param id
 * @param comp
 */
void Game::addComponent(EntityId id, Component *comp) {
    components.components.insert(std::pair<EntityId, Component *>(id, comp));
}

template<typename T>

/**
 * Gets a single component of specified type.
 * @tparam T
 * @param id
 * @return
 */
T *Game::getComponent(EntityId id) {
    for (auto &component : components.components) {
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

    for (auto &component : components.components) {
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

    for (auto &it : components.components) {
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
Game *Game::instance{};
std::mutex Game::mutex;

/**
 * The first time we call getInstance we will lock the storage location
 *      and then we make sure again that the variable is null and then we
 *      set the value.
 */
Game *Game::getInstance() {
    std::lock_guard<std::mutex> lock(mutex);
    if (instance == nullptr) {
        instance = new Game();
    }

    return instance;
}

PhysicsAPI *Game::getPhysicsAPI() {
    return physicsAPI;
}

RenderingAPI *Game::getRenderingApi() {
    return renderingAPI;
}
