#include "ExampleScene.hpp"
#include "../../Game.hpp"
#include "../../Components/PhysicsComponent.h"

void ExampleScene::initialize() {
    Game *game = Game::getInstance();

    EntityId object1 = game->createEntity();
    PhysicsComponent *physicsComponent1 = new PhysicsComponent(object1,
                                                               BodyType::Dynamic,
                                                               Vector2(50, 50),
                                                               Vector2(10, 10));

    // TODO: Create Entity class which stores all the components as smart pointers?
    game->addComponent(object1, physicsComponent1);
}
