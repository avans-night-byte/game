#include <iostream>

#include "./Game.hpp"

// TODO: Remove
#include "../Engine/Engine.hpp"
#include "../API/Input/EngineInputAPI.hpp"
#include "../Engine/Input/Adapter/SDLInputEngineAdapter.hpp"

/**
 * Gameloop does a looptyloop
 **/
void Game::gameLoop()
{

  SDLInputEngineAdapter inputAdapter;
  EngineInputAPI engineInputAPI;

  while (true)
  {
    Input i = engineInputAPI.getInput(inputAdapter);


    /**
     * When the received input contains the action QUIT, call the Engine to close the window and break the game loop.
     * We should move this to an API so we don't call the Engine from the Game.
     **/
    if (i.keyMap.action == "QUIT")
    {
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

