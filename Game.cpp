
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

/**
 * Gameloop
 **/
void Game::gameLoop() {

    SDLInputEngineAdapter *inputAdapter = new SDLInputEngineAdapter();
    EngineInputAPI *engineInputAPI = new EngineInputAPI(inputAdapter);

    Engine *engine = new Engine();

    EngineWindowAPI *engineWindowAPI = new EngineWindowAPI(engine);
    AudioAPI *audioApi = new AudioAPI();

    AudioType s = sound;
    std::string path = "oof.wav";
    audioApi->loadInMemory(path, s);

    // Create Window
    Engine::initWindow(width, height);

    RenderingEngineAdapter renderingEngineAdapter;
    EngineRenderingAPI engineRenderingAPI = EngineRenderingAPI(renderingEngineAdapter, engine);

    // Open Main Menu, this could be the game state
//    MainMenu::init(engineRenderingAPI, engineWindowAPI);
    ExampleScene exampleScene = ExampleScene();
    exampleScene.initialize();

    float timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    SDL_Renderer *renderer = engineWindowAPI->getRenderer();

    const int updateFPS = 60;
    const float deltaTime = 1.0f / updateFPS;

    float elapsedTime = 0.0f;
    float accumulator = 0.0f;

    Uint32 currentTime = SDL_GetTicks();
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

        physicsAPI->DebugDraw(engineRenderingAPI, *renderer);
        SDL_RenderPresent(renderer);

        // Poll input
        Input i = engineInputAPI->getInput();

        // Render Main Menu, this could be game state
//        MainMenu::render(engineRenderingAPI, engineWindowAPI, i);

        // Temporary logger for received Inputs. We will create a logger later.
        debugLog(i);

        /**
        * When the received input contains the action QUIT, call the Engine to close the window and break the game loop.
        * We should move this to an API so we don't call the Engine from the Game.
        **/
        if (i.keyMap.action == "QUIT") {
            EngineRenderingAPI::GetTextureManager()->clearFromTextureMap("boar");
            EngineRenderingAPI::GetTextureManager()->clearFromTextureMap("spritesheets");
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

void Game::initialize() {
    physicsAPI = make_unique<EnginePhysicsAPI>();
}
