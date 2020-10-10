#include <iostream>

#include "./Game.hpp"

// TODO: Remove
#include "../Engine/Engine.hpp"
#include "../API/Input/EngineInputAPI.hpp"
#include "../API/Rendering/EngineRenderingAPI.hpp"

/**
 * Gameloop does a looptyloop
 **/
void Game::gameLoop()
{

  SDLInputEngineAdapter inputAdapter;
  EngineInputAPI engineInputAPI;


  RenderingEngineAdapter renderingEngineAdapter;
  EngineRenderingAPI engineRenderingAPI;


  bool load = EngineRenderingAPI::GetTextureManager()->load("boar.bmp", "boar", Engine::getRenderer());
  Spritesheet* loadSprite = engineRenderingAPI.createSpriteSheet(renderingEngineAdapter, "spritememe.png", "spritesheet", 8, 11, 100, 105, Engine::getRenderer());

  std::cout << load << std::endl;


  loadSprite->select_sprite(0, 0);

  int memer = 0;
  while (true)
  {
    Input i = engineInputAPI.getInput(inputAdapter);

    engineRenderingAPI.drawTexture(renderingEngineAdapter, "boar", 100 + memer / 200, 100, 100, 100, 1, 0, Engine::getRenderer(), SDL_FLIP_NONE);

    loadSprite->draw_selected_sprite(200, 200);
    /**
    * When the received input contains the action QUIT, call the Engine to close the window and break the game loop.
    * We should move this to an API so we don't call the Engine from the Game.
    **/
    if (i.keyMap.action == "QUIT")
    {
      Engine::closeWindow();
      EngineRenderingAPI::GetTextureManager()->clearFromTextureMap("boar");
      break;
    }


    if(i.keyMap.action == "UP"){
        loadSprite->select_sprite(0, 2);
    }
    if(i.keyMap.action == "DOWN"){
          loadSprite->select_sprite(0, 4);
    }
    if(i.keyMap.action == "LEFT"){
      loadSprite->select_sprite(0, 5);
    }

    if(i.keyMap.action == "RIGHT"){
      loadSprite->select_sprite(0, 7);
    }


    // Render the backbuffer.
    SDL_RenderPresent(Engine::getRenderer());
    SDL_RenderClear(Engine::getRenderer());
    memer++;
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
  if (i.keyMap.code != "DEBUG_NO_LOG")
  {
    std::cout << std::endl;
    std::cout << "device: " << i.device << std::endl;
    std::cout << "code: " << i.keyMap.code << std::endl;
    std::cout << "action: " << i.keyMap.action << std::endl;
    std::cout << "x: " << i.x << std::endl;
    std::cout << "y: " << i.y << std::endl;
  }
}


EntityId Game::createEntity(){
    auto it = entities.begin();
    std::advance(it, entities.size());
    EntityId next = (*it) + 1;
    entities.push_back(next);

    return next;
}
void Game::addComponent(EntityId id, Component* comp){
    //This would mean that for every component there is a function with different arguments.
    components.components.insert(std::pair<EntityId, Component *>(id, comp));
    return;
}

template <typename T>
T* Game::getComponent(EntityId id){
    for (auto it = components.components.begin(); it != components.components.end(); ++it) {
        if((it->first == id) && dynamic_cast<const T*>(it->second) != nullptr){
            return (T*)it->second;
        }
    }

    return nullptr;
}

// Get components by Entity.
System<Component> Game::getComponents(EntityId id){
    System<Component> returnComps;

    for (auto it = components.components.begin(); it != components.components.end(); ++it) {
        if(it->first == id){
            returnComps.components.insert(std::pair<EntityId, Component *>(id, it->second));
        }
    }

    return returnComps;
}

// Get components by entity/Type
template <typename T>
System<T> Game::getComponents(EntityId id){
    System<Component> returnComps;

    for (auto it = components.components.begin(); it != components.components.end(); ++it) {
        T* component = dynamic_cast<const T*>(it->second);
        if(it->first == id && component != nullptr){
            returnComps.components.insert(std::pair<EntityId, T*>(id, component));
        }
    }

    return returnComps;
}

