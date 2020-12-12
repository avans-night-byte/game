#include "LevelCharlie.hpp"

#include "../../Game.hpp"
#include "../../Engine/Rendering/TMXLevel.hpp"
#include "../../Components/CharacterComponent.hpp"

void LevelCharlie::render(RenderingAPI &engineRenderingAPI) {
    _level->render(engineRenderingAPI);
}

LevelCharlie::~LevelCharlie() {
    delete _level;
}

LevelCharlie::LevelCharlie(CharacterComponent& characterComponent,
                           RenderingAPI& engineRenderingApi,
                           PhysicsAPI& enginePhysicsApi) : characterComponent(characterComponent) {

    const char *levelName = "../../Resources/LevelCharlie.tmx";
    const char *spritesheetName = "../../Resources/Sprites/Overworld.png";
    const char *spriteId = "Overworld";

    _level = new TMXLevel(levelName, spritesheetName, spriteId, engineRenderingApi, enginePhysicsApi.getPhysicsEngineAdapter());


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


