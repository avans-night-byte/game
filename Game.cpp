#include <iostream>

#include "./Game.hpp"

// TODO: Remove
#include "../Engine/Engine.hpp"
#include "../API/Input/EngineInputAPI.hpp"
#include "../Engine/Input/Adapter/SDLInputEngineAdapter.hpp"

void Game::gameLoop()
{

  SDLInputEngineAdapter inputAdapter;
  EngineInputAPI engineInputAPI;

  while (true)
  {
    Input i = engineInputAPI.getInput(inputAdapter);

    debugLog(i);

    if (i.keyMap.action == "QUIT")
    {
      Engine::closeWindow();
    }
  }
}

void Game::debugLog(Input i)
{
  std::cout << std::endl;
  std::cout << "device: " << i.device << std::endl;
  std::cout << "code: " << i.keyMap.code << std::endl;
  std::cout << "action: " << i.keyMap.action << std::endl;
  std::cout << "x: " << i.x << std::endl;
  std::cout << "y: " << i.y << std::endl;
}