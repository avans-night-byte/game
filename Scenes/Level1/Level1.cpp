//
// Created by sascha on 11/27/20.
//

#include "Level1.hpp"
#include "../../Components/PhysicsComponent.h"

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

}
