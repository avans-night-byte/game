#include <iostream>

#include "./MainMenu.hpp"

Spritesheet *characterSpriteSheet;
Spritesheet *buttonSpriteSheet;
Spritesheet *settingsSpriteSheet;

// Coords
int menuButtonWidth = 779;
int menuButtonHeight = 108;
int menuButtonX = 100;
int playButtonY = 26;
int helpButtonY = 152;
int creditsButtonY = 278;
int exitButtonY = 704;
// Draw settings buttons
int settingFadeX = 1680;
int settingsFadeY = 925;
int settingsBarX = 1760;
int settingsBarY = 940;

void MainMenu::init(EngineRenderingAPI *engineRenderingAPI, EngineWindowAPI *engineWindowAPI, AudioAPI *audioApi)
{
  // Load textures
  engineRenderingAPI->loadTexture("../../Resources/Sprites/background.png", "background");
  engineRenderingAPI->loadTexture("../../Resources/Sprites/menu_bar.png", "menu_bar");

  // Background music
  AudioType s = sound;
  std::string path = "../../Resources/Sounds/background.wav";
  audioApi->playFromPath(path, s);

  // Load sprites
  characterSpriteSheet = engineRenderingAPI->createSpriteSheet("../../Resources/Sprites/character.png", "spritesheet_char", 8, 11, 100, 105);
  buttonSpriteSheet = engineRenderingAPI->createSpriteSheet("../../Resources/Sprites/main_menu_buttons.png", "spritesheet_buttons", 2, 3, 914, 226);
  settingsSpriteSheet = engineRenderingAPI->createSpriteSheet("../../Resources/Sprites/settings.png", "spritesheet_settings", 0, 4, 232, 122);

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
  engineRenderingAPI->drawTexture("menu_bar", 60, -45, 990, 1170, 1, 1);

  // Play Button
  buttonSpriteSheet->select_sprite(0, 0);
  buttonSpriteSheet->draw_selected_sprite(menuButtonX, playButtonY);

  buttonSpriteSheet->select_sprite(0, 1);
  buttonSpriteSheet->draw_selected_sprite(menuButtonX, helpButtonY);

  buttonSpriteSheet->select_sprite(0, 2);
  buttonSpriteSheet->draw_selected_sprite(menuButtonX, creditsButtonY);

  buttonSpriteSheet->select_sprite(1, 0);
  buttonSpriteSheet->draw_selected_sprite(menuButtonX, exitButtonY);

  settingsSpriteSheet->select_sprite(0, 1);
  settingsSpriteSheet->draw_selected_sprite(settingFadeX, settingsFadeY);
  settingsSpriteSheet->select_sprite(0, 3);
  settingsSpriteSheet->draw_selected_sprite(1920 - 157, 1080 - 140);
  settingsSpriteSheet->select_sprite(0, 0);
  settingsSpriteSheet->draw_selected_sprite(1920 - 215, 1080 - 130);
  settingsSpriteSheet->select_sprite(0, 2);
  settingsSpriteSheet->draw_selected_sprite(1920 - 145, 1080 - 147);

  // Click on menu buttons
  if (i.keyMap.action == "CLICK_LEFT")
  {
    clicked(i.x, i.y);
  }
}

void MainMenu::clicked(int x, int y)
{
  std::cout << "CLICKED!" << std::endl;
  if (x >= menuButtonX && y >= playButtonY 
  && x <= (menuButtonX + menuButtonWidth) && y <= (playButtonY + menuButtonHeight))
  {
    std::cout << "Clicked PLAY button" << std::endl;
  }
}
