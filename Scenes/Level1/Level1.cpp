#include "Level1.hpp"

#include "../../Game.hpp"
#include "../../Components/CharacterComponent.hpp"
#include "../../Engine/Rendering/TMXLevel.hpp"

void Level1::render() {
    _level->render(Game::getInstance()->getRenderingApi());
}

Level1::~Level1() {
    delete _level;
}

Level1::Level1(TMXLevel* tmxLevel, CharacterComponent *characterComponent) : characterComponent(characterComponent) {
    _level = tmxLevel;
}


void Level1::fixedUpdate(const float &deltaTime) {
    characterComponent->fixedUpdate(deltaTime);
}

void Level1::update(const Input &inputSystem) {
    characterComponent->update(inputSystem);
}
