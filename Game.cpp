
#include <iostream>

#include "./Game.hpp"
#include "../API/Input/EngineInputAPI.hpp"
#include "../API/Rendering/EngineRenderingAPI.hpp"
#include "../API/Engine/EngineWindowAPI.hpp"
#include "../API/Physics/EnginePhysicsAPI.hpp"

// Fixme: No hardie
#include "./Scenes/Menu/MainMenu.cpp"
#include "./Scenes/Example/ExampleScene.hpp"
#include "./Scenes/Credits/Credits.hpp"
#include "./Scenes/Level1/Level1.hpp"

typedef signed int int32;

const int width = 1920;
const int height = 1080;

Engine *engine;
EngineInputAPI *engineInputAPI;
EngineWindowAPI *engineWindowAPI;
EngineRenderingAPI *engineRenderingAPI;
unique_ptr<PhysicsAPI> physicsAPI;
AudioAPI *audioApi;

int currentState = 1;


void Game::initialize()
{
    Engine::initWindow(width, height);
    engineRenderingAPI = new EngineRenderingAPI(engine);
    engineInputAPI = new EngineInputAPI();
    engineWindowAPI = new EngineWindowAPI(engine);
    audioApi = new AudioAPI();
    physicsAPI = make_unique<EnginePhysicsAPI>();

    

    // We should normally init when switching state.
    Credits::init(engineRenderingAPI, engineWindowAPI, audioApi);
}

/**
 * Gameloop
 **/
void Game::gameLoop()
{
    // Open Main Menu, this could be the game state
    unique_ptr<ExampleScene> exampleScene = nullptr;

    unique_ptr<MainMenu> mainMenu = make_unique<MainMenu>(engineRenderingAPI, engineWindowAPI, audioApi);

    unique_ptr<Level1> level1 = nullptr;

    bool isDebuggingPhysics = false;

    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    const int updateFPS = 60;
    const float deltaTime = 1.0f / updateFPS;

    float elapsedTime = 0.0f;
    float accumulator = 0.0f;

    // TODO: Move
    Uint32 currentTime = SDL_GetTicks();

    bool isDebuggingPhysics = false;

    // Gameloop
    while (true)
    {
        // Poll input and keep track of lastInput
        Input i = engineInputAPI->getInput();
        debugLog(i);

        /**   PHYSICS      */
        auto newTime = std::chrono::high_resolution_clock::now();

        // Gets the time in microseconds and converts them into seconds.
        float frameTime = std::chrono::duration_cast<std::chrono::microseconds>(newTime - currentTime).count() / 100000.0f;

        currentTime = newTime;
        accumulator += frameTime;

        while (accumulator >= dt)
        {
            physicsAPI->update(dt, velocityIterations, positionIterations);
            if (exampleScene)
            {
                exampleScene->fixedUpdate(dt);
            }

            elapsedTime += deltaTime;
            accumulator -= deltaTime;
        }

        // Poll input and keep track of lastInput
        Input i = engineInputAPI->getInput();
        debugLog(i);

        if (i.keyMap.action == "1" || i.keyMap.action == "2" || i.keyMap.action == "3" || i.keyMap.action == "4")
        {
            setCurrentState(std::stoi(i.keyMap.action));
        }

        // Temporary State
        if (currentState == 1)
        {
            mainMenu->render(engineRenderingAPI, engineWindowAPI, i);
        }

        if (currentState == 2)
        {
            Credits::render(engineRenderingAPI, engineWindowAPI, i);
        }

        if (currentState == 3)
        {
            if (exampleScene == nullptr)
            {
                exampleScene = make_unique<ExampleScene>(engineRenderingAPI);
                exampleScene->initialize();
            }
            // TODO: Move
            SDL_SetRenderDrawColor(engineWindowAPI->getRenderer(), 0, 0, 0, SDL_ALPHA_OPAQUE);
            SDL_RenderClear(engineWindowAPI->getRenderer());

            physicsAPI->DebugDraw(*engineRenderingAPI, *engineWindowAPI->getRenderer());
        }

        if (currentState == 4)
        {
            if (level1 == nullptr)
            {
                level1 = make_unique<Level1>(*engineRenderingAPI);
            }
            level1->render(*engineRenderingAPI);
            level1->update(i);
            level1->fixedUpdate(dt);
        }

        physicsAPI->DebugDraw(*engineRenderingAPI, *engineWindowAPI->getRenderer());

        SDL_RenderPresent(engineWindowAPI->getRenderer());
        SDL_RenderClear(engineWindowAPI->getRenderer());

        if (currentState == 0)
        {
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
void Game::debugLog(Input i)
{
    if (i.device != Input::NONE)
    {
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
EntityId Game::createEntity()
{
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
void Game::addComponent(EntityId id, Component *comp)
{
    components.components.insert(std::pair<EntityId, Component *>(id, comp));
}

template <typename T>

/**
 * Gets a single component of specified type.
 * @tparam T
 * @param id
 * @return
 */
T *Game::getComponent(EntityId id)
{
    for (auto &component : components.components)
    {
        if ((component.first == id) && dynamic_cast<const T *>(component.second) != nullptr)
        {
            return (T *)component.second;
        }
    }

    return nullptr;
}

/**
 * Gets components by entity id of all types.
 * @param id
 * @return
 */
System<Component> Game::getComponents(EntityId id)
{
    System<Component> returnComps;

    for (auto &component : components.components)
    {
        if (component.first == id)
        {
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
template <typename T>
System<T> Game::getComponents(EntityId id)
{
    System<Component> returnComps;

    for (auto &it : components.components)
    {
        T *component = dynamic_cast<const T *>(it.second);
        if (it.first == id && component != nullptr)
        {
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
Game *Game::getInstance()
{
    std::lock_guard<std::mutex> lock(mutex);
    if (instance == nullptr)
    {
        instance = new Game();
    }

    return instance;
}

const PhysicsAPI *Game::getPhysicsAPI()
{
    return physicsAPI;
}

void Game::setCurrentState(int state)
{
    currentState = state;
}

