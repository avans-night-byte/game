
#include <iostream>

#include "./Game.hpp"
#include "../API/Input/EngineInputAPI.hpp"
#include "../API/Rendering/EngineRenderingAPI.hpp"
#include "../API/Engine/EngineWindowAPI.hpp"
#include "../API/Physics/EnginePhysicsAPI.hpp"

// Fixme: No hardie
#include "./Scenes/Menu/MainMenu.cpp"
#include "Scenes/Example/ExampleScene.hpp"

typedef signed int int32;

const int width = 1920;
const int height = 1080;

Engine *engine;
EngineInputAPI *engineInputAPI;
EngineWindowAPI *engineWindowAPI;
EngineRenderingAPI *engineRenderingAPI;
unique_ptr<PhysicsAPI> physicsAPI;
AudioAPI *audioApi;

void Game::initialize() {
    Engine::initWindow(width, height);
    engineRenderingAPI = new EngineRenderingAPI(engine);
    engineInputAPI = new EngineInputAPI();
    engineWindowAPI = new EngineWindowAPI(engine);
    audioApi = new AudioAPI();
    physicsAPI = make_unique<EnginePhysicsAPI>();

    // Open Main Menu, this could be the game state
    MainMenu::init(engineRenderingAPI, engineWindowAPI, audioApi);
}

/**
 * Gameloop
 **/
void Game::gameLoop() {
    AudioType s = sound;
    std::string path = "oof.wav";
    audioApi->loadInMemory(path, s);

    // Open Main Menu, this could be the game state
    unique_ptr<ExampleScene> exampleScene = nullptr;

    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    SDL_Renderer *renderer = engineWindowAPI->getRenderer();

    const int updateFPS = 60;
    const float deltaTime = 1.0f / updateFPS;

    float elapsedTime = 0.0f;
    float accumulator = 0.0f;

    Uint32 currentTime = SDL_GetTicks();

    bool isDebuggingPhysics = false;
    // Gameloop
    while (true) {

        const Uint32 newTime = SDL_GetTicks();
        float frameTime = static_cast<float> (newTime - currentTime) / 250.0f;

        if(frameTime > 0.25f)
            frameTime = 0.25f;

        currentTime = newTime;
        accumulator += frameTime;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        while(accumulator >= deltaTime)
        {
            physicsAPI->update(deltaTime, velocityIterations, positionIterations);

            elapsedTime += deltaTime;
            accumulator -= deltaTime;
        }

        // Poll input
        Input i = engineInputAPI->getInput();

        if(i.keyMap.action == "1")
        {
            isDebuggingPhysics = true;
        }

        if(!isDebuggingPhysics)
        {
            // Render Main Menu, this could be game state
            MainMenu::render(engineRenderingAPI, engineWindowAPI, i);
        }
        else
        {
            if(exampleScene == nullptr)
            {
                exampleScene = make_unique<ExampleScene>();
                exampleScene->initialize();
            }
            physicsAPI->DebugDraw(*engineRenderingAPI, *renderer);
        }


        SDL_RenderPresent(engineWindowAPI->getRenderer());
        SDL_RenderClear(engineWindowAPI->getRenderer());
        // Temporary logger for received Inputs. We will create a logger later.
        debugLog(i);

        if (i.keyMap.action == "QUIT") {
            engineWindowAPI->closeWindow();
            break;
        }
    }
}

/**
 * Logs Input struct properties that have been received by the game loop. 
 * 
 * For testing purposes only, we should create a generic logger someday.
 * 
 * @param Input An Input struct
 **/
void Game::debugLog(Input i) {
    if (i.device != Input::NONE) {
        std::cout << std::endl;
        std::cout << "device: " << i.device << std::endl;
        std::cout << "code: " << i.keyMap.code << std::endl;
        std::cout << "action: " << i.keyMap.action << std::endl;
        std::cout << "x: " << i.x << std::endl;
        std::cout << "y: " << i.y << std::endl;
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
 * The first time we call GetInstance we will lock the storage location
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

const unique_ptr<PhysicsAPI> &Game::getPhysicsAPI() {
    return physicsAPI;
}

