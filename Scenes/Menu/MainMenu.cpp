#include "./MainMenu.hpp"

#include "../../API/Rendering/EngineRenderingAPI.hpp"
#include "../../API/Audio/AudioAPI.hpp"

MainMenu::MainMenu(EngineRenderingAPI *engineRenderingAPI, EngineWindowAPI *engineWindowAPI, AudioAPI *audioApi)
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
  buttonSpriteSheet = engineRenderingAPI->createSpriteSheet("../../Resources/Sprites/main_menu_buttons.png", "spritesheet_buttons", 2, 3, 779, 112);
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

  // Menu buttons
  buttonSpriteSheet->select_sprite(0, 0);
  buttonSpriteSheet->draw_selected_sprite(menuButtonX, playButtonY);
  buttonSpriteSheet->select_sprite(0, 1);
  buttonSpriteSheet->draw_selected_sprite(menuButtonX, helpButtonY);
  buttonSpriteSheet->select_sprite(0, 2);
  buttonSpriteSheet->draw_selected_sprite(menuButtonX, creditsButtonY);
  buttonSpriteSheet->select_sprite(1, 0);
  buttonSpriteSheet->draw_selected_sprite(menuButtonX, exitButtonY);

  // Settings buttons
  settingsSpriteSheet->select_sprite(0, 1);
  settingsSpriteSheet->draw_selected_sprite(settingsFadeX, settingsFadeY);
  settingsSpriteSheet->select_sprite(0, 3);
  settingsSpriteSheet->draw_selected_sprite(settingsBarX, settingsButtonY);
  settingsSpriteSheet->select_sprite(0, 0);
  settingsSpriteSheet->draw_selected_sprite(githubButtonX, settingsButtonY + 10);
  settingsSpriteSheet->select_sprite(0, 2);
  settingsSpriteSheet->draw_selected_sprite(settingsButtonX, settingsButtonY - 10);

  // Click on menu buttons
  if (i.keyMap.action == "CLICK_LEFT")
  {
    if (clicked(i, menuButtonX, playButtonY))
    {
      std::cout << "Clicked PLAY button" << std::endl;
      Game::setCurrentState(4);
    }

    if (clicked(i, menuButtonX, helpButtonY))
    {
      std::cout << "Clicked HELP button" << std::endl;
    }

    if (clicked(i, menuButtonX, creditsButtonY))
    {
      std::cout << "Clicked CREDITS button" << std::endl;
      Game::setCurrentState(2);
    }

    if (clicked(i, menuButtonX, exitButtonY))
    {
      std::cout << "Clicked EXIT button" << std::endl;
      Game::setCurrentState(0);
    }
  }
}

bool MainMenu::clicked(Input i, int x, int y) const
{
  return (i.x >= x && i.y >= y && i.x <= (x + menuButtonWidth) && i.y <= (y + menuButtonHeight));
}


