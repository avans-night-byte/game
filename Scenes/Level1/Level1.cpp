#include "Level1.hpp"

#include "../../Game.hpp"
#include "../../Components/CharacterComponent.hpp"
#include "../../Engine/Rendering/TMXLevel.hpp"

void Level1::render() {
    _level->render(*Game::getInstance()->getRenderingApi());
}

Level1::~Level1() {
    delete _level;
}

Level1::Level1(TMXLevel* tmxLevel, CharacterComponent *characterComponent) : characterComponent(characterComponent) {
    _level = tmxLevel;
    Game *game = Game::getInstance();

//    EntityId object1 = game->createEntity();
//    auto *physicsComponent1 = new PhysicsComponent(object1,
//                                                   BodyType::Dynamic,
//                                                   Vector2(129, 0),
//                                                   Vector2(10, 10));

//    game->addComponent(object1, physicsComponent1);
}


void Level1::fixedUpdate(const float &deltaTime) {
    characterComponent->fixedUpdate(deltaTime);
}

void Level1::update(const Input &inputSystem) {
    characterComponent->update(inputSystem);
}
