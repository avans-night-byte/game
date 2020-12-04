#pragma once

#include "memory"
#include <iostream>

class Spritesheet;
class EngineRenderingAPI;
class EngineWindowAPI;
class AudioAPI;

class MainMenu
{
private:
    Spritesheet *characterSpriteSheet;
    Spritesheet *buttonSpriteSheet;
    Spritesheet *settingsSpriteSheet;

    // Coords
    int menuButtonWidth = 779;
    int menuButtonHeight = 108;
    int menuButtonX = 170;
    int playButtonY = 150;
    int helpButtonY = 300;
    int creditsButtonY = 450;
    int exitButtonY = 750;

    int settingsFadeX = 1680;
    int settingsFadeY = 925;
    int settingsButtonY = 940;
    int githubButtonX = 1705;
    int settingsButtonX = 1775;
    int settingsBarX = 1760;

public:
    MainMenu(EngineRenderingAPI *renderAPI, EngineWindowAPI *engineWindowAPI, AudioAPI *audioApi);

    void render(EngineRenderingAPI *renderAPI, EngineWindowAPI *engineWindowAPI, Input i);

    bool clicked(Input i, int x, int y) const;
};