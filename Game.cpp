#include <iostream>

#include "./Game.hpp"
#include "../API/Input/EngineInputAPI.hpp"
#include "../API/Rendering/EngineRenderingAPI.hpp"
#include "../API/Engine/EngineWindowAPI.hpp"

// Fixme: No hardie
#include "./Scenes/Menu/MainMenu.cpp"

const int width = 1920;
const int height = 1080;

/**
 * Gameloop
 **/
void Game::gameLoop()
{

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
    MainMenu::init(engineRenderingAPI, engineWindowAPI);

    // Gameloop
    while (true)
    {
        // Poll input
        Input i = engineInputAPI->getInput();

        // Render Main Menu, this could be game state
        MainMenu::render(engineRenderingAPI, engineWindowAPI, i);

        // Temporary logger for received Inputs. We will create a logger later.
        debugLog(i);

        /**
        * When the received input contains the action QUIT, call the Engine to close the window and break the game loop.
        * We should move this to an API so we don't call the Engine from the Game.
        **/
        if (i.keyMap.action == "QUIT")
        {
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
