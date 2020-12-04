#include "LevelCharlie.hpp"

#include "../../Game.hpp"
#include "../../Engine/Rendering/Level.hpp"
#include "../../Components/CharacterComponent.h"

void LevelCharlie::render(EngineRenderingAPI &engineRenderingAPI) {
    _level->render(engineRenderingAPI);
}

LevelCharlie::~LevelCharlie() {
    delete _level;
}

LevelCharlie::LevelCharlie(CharacterComponent& characterComponent,
                           EngineRenderingAPI& engineRenderingApi,
                           PhysicsAPI& enginePhysicsApi) : characterComponent(characterComponent) {

    const char *levelName = "../../Resources/LevelCharlie.tmx";
    const char *spritesheetName = "../../Resources/Sprites/Overworld.png";
    const char *spriteId = "Overworld";

    _level = new Level( levelName, spritesheetName, spriteId, engineRenderingApi, *enginePhysicsApi.getPhysicsEngineAdapter());


    Game *game = Game::getInstance();

    EntityId object1 = game->createEntity();
    auto *physicsComponent1 = new PhysicsComponent(object1,
                                                   BodyType::Dynamic,
                                                   Vector2(129, 0),
                                                   Vector2(10, 10));

    game->addComponent(object1, physicsComponent1);
}


void LevelCharlie::fixedUpdate(const float &deltaTime) {
    characterComponent.fixedUpdate(deltaTime);
}

void LevelCharlie::update(const Input &inputSystem) {
    characterComponent.update(inputSystem);
}


