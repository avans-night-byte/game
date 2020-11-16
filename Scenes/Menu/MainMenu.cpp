#include <iostream>

#include "./MainMenu.hpp"

Spritesheet *characterSpriteSheet;
Spritesheet *buttonSpriteSheet;

void MainMenu::init(EngineRenderingAPI *engineRenderingAPI, EngineWindowAPI *engineWindowAPI)
{
  // Load textures
  bool background = engineRenderingAPI->loadTexture("../../Resources/Sprites/background.png", "background");
  bool boar = engineRenderingAPI->loadTexture("../../Resources/Sprites/boar.png", "boar");

  // Load sprites
  characterSpriteSheet = engineRenderingAPI->createSpriteSheet("../../Resources/Sprites/character.png", "spritesheet_char", 8, 11, 100, 105);
  buttonSpriteSheet = engineRenderingAPI->createSpriteSheet("../../Resources/Sprites/buttons.png", "spritesheet_buttons", 2, 3, 914, 226);

  // Init character state
  characterSpriteSheet->select_sprite(0, 0);
}

void MainMenu::render(EngineRenderingAPI *engineRenderingAPI, EngineWindowAPI *engineWindowAPI, Input i)
{

  // Draw background image
  engineRenderingAPI->drawTexture("background", 0, 0, 1920, 1080, 1, 1);

  // Draw boar image
  engineRenderingAPI->drawTexture("boar", 1920-220, 1080-220, 200, 200, 1, 1);

  // Character Movement Demo
  if (i.keyMap.action == "UP")
  {
    characterSpriteSheet->select_sprite(0, 2);
  }
  if (i.keyMap.action == "DOWN")
  {
    characterSpriteSheet->select_sprite(0, 4);
  }
  if (i.keyMap.action == "LEFT")
  {
    characterSpriteSheet->select_sprite(0, 5);
  }
  if (i.keyMap.action == "RIGHT")
  {
    characterSpriteSheet->select_sprite(0, 7);
  }

  characterSpriteSheet->draw_selected_sprite(0, 0);

  // Draw buttons
  buttonSpriteSheet->select_sprite(0, 0);
  buttonSpriteSheet->draw_selected_sprite(100, 26);

  buttonSpriteSheet->select_sprite(0, 1);
  buttonSpriteSheet->draw_selected_sprite(100, 152);

  buttonSpriteSheet->select_sprite(0, 2);
  buttonSpriteSheet->draw_selected_sprite(100, 278);

  buttonSpriteSheet->select_sprite(1, 0);
  buttonSpriteSheet->draw_selected_sprite(100, 704);

  // Render the backbuffer.
  SDL_RenderPresent(engineWindowAPI->getRenderer());
  SDL_RenderClear(engineWindowAPI->getRenderer());
}