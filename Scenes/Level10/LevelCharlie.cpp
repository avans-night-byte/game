#include "LevelCharlie.hpp"

void LevelCharlie::render(EngineRenderingAPI &engineRenderingAPI) {
    _level->render(engineRenderingAPI);
}

LevelCharlie::~LevelCharlie() {
    delete _level;
}

LevelCharlie::LevelCharlie(EngineRenderingAPI& engineRenderingApi) {
    const char *levelName = "../../Resources/LevelCharlie.tmx";
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
    characterComponent = make_unique<CharacterComponent>(characterEntityId, &engineRenderingApi, Vector2(100, 250));

    game->addComponent(characterEntityId, characterComponent.get());
}


void LevelCharlie::fixedUpdate(const float &deltaTime) {
    characterComponent->fixedUpdate(deltaTime);
}

void LevelCharlie::update(const Input &inputSystem) {
    characterComponent->update(inputSystem);
}


