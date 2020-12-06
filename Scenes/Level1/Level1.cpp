#include "Level1.hpp"

#include "../../Game.hpp"
#include "../../Components/CharacterComponent.hpp"
#include "../../Engine/Rendering/TMXLevel.hpp"

void Level1::render(RenderingAPI &renderingApi) {
    _level->render(renderingApi);
}

Level1::~Level1() {
    delete _level;
}

Level1::Level1(CharacterComponent& characterComponent,
               RenderingAPI& renderingApi,
               PhysicsAPI& enginePhysicsApi) : characterComponent(characterComponent) {

    const char *levelName = "../../Resources/example.tmx";
    const char *spritesheetName = "../../Resources/Sprites/Overworld.png";
    const char *spriteId = "Overworld";

    _level = new TMXLevel(levelName, spritesheetName, spriteId, renderingApi, *enginePhysicsApi.getPhysicsEngineAdapter());


    Game *game = Game::getInstance();

    EntityId object1 = game->createEntity();
    auto *physicsComponent1 = new PhysicsComponent(object1,
                                                   BodyType::Dynamic,
                                                   Vector2(129, 0),
                                                   Vector2(10, 10));

    game->addComponent(object1, physicsComponent1);
}


void Level1::fixedUpdate(const float &deltaTime) {
    characterComponent.fixedUpdate(deltaTime);
}

void Level1::update(const Input &inputSystem) {
    characterComponent.update(inputSystem);
}
