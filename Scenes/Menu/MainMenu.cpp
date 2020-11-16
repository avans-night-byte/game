#include <iostream>

#include "./MainMenu.hpp"

Spritesheet *characterSpriteSheet;
Spritesheet *buttonSpriteSheet;
Spritesheet *settingsSpriteSheet;

void MainMenu::init(EngineRenderingAPI *engineRenderingAPI, EngineWindowAPI *engineWindowAPI)
{
  // Load textures
  bool background = engineRenderingAPI.loadTexture("../../Resources/Sprites/background.png", "background");
  bool menu_bar = engineRenderingAPI.loadTexture("../../Resources/Sprites/menu_bar.png", "menu_bar");

  // Load sprites
  characterSpriteSheet = engineRenderingAPI.createSpriteSheet("../../Resources/Sprites/character.png", "spritesheet_char", 8, 11, 100, 105);
  buttonSpriteSheet = engineRenderingAPI.createSpriteSheet("../../Resources/Sprites/buttons.png", "spritesheet_buttons", 2, 3, 914, 226);
  settingsSpriteSheet = engineRenderingAPI.createSpriteSheet("../../Resources/Sprites/settings.png", "spritesheet_settings", 0, 4, 232, 122);

  // Init character state
  characterSpriteSheet->select_sprite(0, 0);
}

void MainMenu::render(EngineRenderingAPI *engineRenderingAPI, EngineWindowAPI *engineWindowAPI, Input i)
{

  // Draw background image
  engineRenderingAPI->drawTexture("background", 0, 0, 1920, 1080, 1, 1);

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
  engineRenderingAPI.drawTexture("menu_bar", 60, 0, 990, 1080, 1, 1);

  buttonSpriteSheet->select_sprite(0, 0);
  buttonSpriteSheet->draw_selected_sprite(100, 26);

  buttonSpriteSheet->select_sprite(0, 1);
  buttonSpriteSheet->draw_selected_sprite(100, 152);

  buttonSpriteSheet->select_sprite(0, 2);
  buttonSpriteSheet->draw_selected_sprite(100, 278);

  buttonSpriteSheet->select_sprite(1, 0);
  buttonSpriteSheet->draw_selected_sprite(100, 704);

  // Draw settings buttons
  settingsSpriteSheet->select_sprite(0, 1);
  settingsSpriteSheet->draw_selected_sprite(1920-240, 1080-155);
  settingsSpriteSheet->select_sprite(0, 3);
  settingsSpriteSheet->draw_selected_sprite(1920-157, 1080-140);
  settingsSpriteSheet->select_sprite(0, 0);
  settingsSpriteSheet->draw_selected_sprite(1920-215, 1080-130);
  settingsSpriteSheet->select_sprite(0, 2);
  settingsSpriteSheet->draw_selected_sprite(1920-145, 1080-147);


  // Render the backbuffer.
  SDL_RenderPresent(engineWindowAPI->getRenderer());
  SDL_RenderClear(engineWindowAPI->getRenderer());
}