#pragma once

class MainMenu {
private:

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
public:
    MainMenu(EngineRenderingAPI *renderAPI, EngineWindowAPI *engineWindowAPI, AudioAPI *audioApi);

//    static void init();

    void render(EngineRenderingAPI *renderAPI, EngineWindowAPI *engineWindowAPI, Input i);

    void clicked(int x, int y) const;
};