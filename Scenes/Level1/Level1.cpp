//
// Created by sascha on 11/27/20.
//

#include "Level1.hpp"
#include "../../Components/PhysicsComponent.h"
#include "../../Components/CharacterComponent.h"

void Level1::render(EngineRenderingAPI &engineRenderingAPI) {
    _level->render(engineRenderingAPI);
}

Level1::~Level1() {
    delete _level;
}

Level1::Level1(EngineRenderingAPI& engineRenderingApi) {
    const char *levelName = "../../Resources/example.tmx";
    const char *spritesheetName = "../../Resources/Sprites/Overworld.png";
    const char *spriteId = "Overworld";

    _level = new Level( levelName, spritesheetName, spriteId, engineRenderingApi);


    Game *game = Game::getInstance();

    EntityId object1 = game->createEntity();
    auto *physicsComponent1 = new PhysicsComponent(object1,
                                                               BodyType::Dynamic,
                                                               Vector2(129, 0),
                                                               Vector2(10, 10));

    game->addComponent(object1, physicsComponent1);

    EntityId characterEntityId;
    characterEntityId = game->createEntity();
    characterComponent = make_unique<CharacterComponent>(characterEntityId, &engineRenderingApi, Vector2(30, 30));

    game->addComponent(characterEntityId, characterComponent.get());

}


void Level1::fixedUpdate(const float &deltaTime) {
    characterComponent->fixedUpdate(deltaTime);
}

void Level1::update(const Input &inputSystem) {
    characterComponent->update(inputSystem);
}


