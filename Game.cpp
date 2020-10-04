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

    debugLog(i);

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