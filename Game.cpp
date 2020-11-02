#include <iostream>

#include "./Game.hpp"

// TODO: Remove
#include "../Engine/Engine.hpp"
#include "../API/Input/EngineInputAPI.hpp"
#include "../API/Rendering/EngineRenderingAPI.hpp"

/**
 * Gameloop does a looptyloop
 **/
void Game::gameLoop() {

    SDLInputEngineAdapter inputAdapter;
    EngineInputAPI engineInputAPI;

    RenderingEngineAdapter renderingEngineAdapter;
    auto engineRenderingAPI = EngineRenderingAPI(renderingEngineAdapter);

    bool load = engineRenderingAPI.loadTexture("boar.bmp", "boar");
    Spritesheet *loadSprite = engineRenderingAPI.createSpriteSheet("spritememe.png", "spritesheet", 8, 11, 100, 105);

    std::cout << load << std::endl;

    //Select a sprite based on the width/ height specified in creating the spritesheet.
    loadSprite->select_sprite(0, 0);

    while (true) {
        Input i = engineInputAPI.getInput(inputAdapter);
        loadSprite->draw_selected_sprite(200, 200);

        if (i.keyMap.action == "UP") {
            loadSprite->select_sprite(0, 2);
        }
        if (i.keyMap.action == "DOWN") {
            loadSprite->select_sprite(0, 4);
        }
        if (i.keyMap.action == "LEFT") {
            loadSprite->select_sprite(0, 5);
        }

        if (i.keyMap.action == "RIGHT") {
            loadSprite->select_sprite(0, 7);
        }

        // Render the backbuffer.
        SDL_RenderPresent(Engine::getRenderer());
        SDL_RenderClear(Engine::getRenderer());

        /**
        * When the received input contains the action QUIT, call the Engine to close the window and break the game loop.
        * We should move this to an API so we don't call the Engine from the Game.
        **/
        if (i.keyMap.action == "QUIT") {
            EngineRenderingAPI::GetTextureManager()->clearFromTextureMap("boar");
            EngineRenderingAPI::GetTextureManager()->clearFromTextureMap("spritesheets");
            Engine::closeWindow();
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
    if (i.keyMap.code != "DEBUG_NO_LOG") {
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

