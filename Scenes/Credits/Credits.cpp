#include "Credits.hpp"

Spritesheet *avatarSpriteSheet;
Spritesheet *namesSpriteSheet;


void Credits::init(RenderingAPI *renderAPI, EngineWindowAPI *engineWindowAPI, AudioAPI *audioApi) {
    // Load Textures
    renderAPI->loadTexture("../../Resources/Sprites/background.png", "background");
    renderAPI->loadTexture("../../Resources/Sprites/UI/credits-bg.png", "credits_bg");
    renderAPI->loadTexture("../../Resources/Sprites/UI/credits-header.png", "credits_header");
    renderAPI->loadTexture("../../Resources/Sprites/UI/button-back.png", "button_back");

    // Load Sprites
    avatarSpriteSheet = renderAPI->createSpriteSheet("../../Resources/Sprites/UI/credits-avatars-smaller.png", "spritesheet_avatar", 2, 3, 270, 270);
    namesSpriteSheet = renderAPI->createSpriteSheet("../../Resources/Sprites/UI/credits-names.png", "spritesheet_names", 2, 3, 240, 100);
}

void Credits::render(RenderingAPI *renderAPI, EngineWindowAPI *engineWindowAPI, Input i) {
    // Draw Textures
    renderAPI->drawTexture("background", 0, 0, 1920, 1080, 1, 1);
    renderAPI->drawTexture("credits_bg", 500, 0, 1600, 1750, .6, 1);
    renderAPI->drawTexture("credits_header", 590, 20, 1293, 285, .6, 1);
    renderAPI->drawTexture("button_back", 710, 880, 910, 180, .6, 1);

    // Huseyin
    avatarSpriteSheet->select_sprite(0, 0);
    avatarSpriteSheet->draw_selected_sprite(610, 140);

    namesSpriteSheet->select_sprite(0, 0);
    namesSpriteSheet->draw_selected_sprite(610, 140+200);

    // Martijn
    avatarSpriteSheet->select_sprite(1, 0);
    avatarSpriteSheet->draw_selected_sprite(610+230, 140);

    namesSpriteSheet->select_sprite(1, 0);
    namesSpriteSheet->draw_selected_sprite(610+250, 140+200);

    // Yannick
    avatarSpriteSheet->select_sprite(0, 1);
    avatarSpriteSheet->draw_selected_sprite(610+230+230, 140);

    namesSpriteSheet->select_sprite(2, 0);
    namesSpriteSheet->draw_selected_sprite(610+250+250, 140+200);

    // Marco
    avatarSpriteSheet->select_sprite(1, 1);
    avatarSpriteSheet->draw_selected_sprite(610, 180+310);

    namesSpriteSheet->select_sprite(0, 1);
    namesSpriteSheet->draw_selected_sprite(610, 700);

    // Storm
    avatarSpriteSheet->select_sprite(2, 0);
    avatarSpriteSheet->draw_selected_sprite(610+230, 180+310);

    namesSpriteSheet->select_sprite(1, 1);
    namesSpriteSheet->draw_selected_sprite(610+250, 700);

    // Sascha
    avatarSpriteSheet->select_sprite(2, 1);
    avatarSpriteSheet->draw_selected_sprite(610+230+230, 180+310);

    namesSpriteSheet->select_sprite(2, 1);
    namesSpriteSheet->draw_selected_sprite(610+250+250, 700);
}
