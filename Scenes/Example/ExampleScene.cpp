#include "ExampleScene.hpp"
#include "../../Game.hpp"
#include "../../Components/PhysicsComponent.h"

void ExampleScene::initialize() {
    Game *game = Game::getInstance();

    EntityId object1 = game->createEntity();
    PhysicsComponent *physicsComponent1 = new PhysicsComponent(object1,
                                                               BodyType::Dynamic,
                                                               Vector2(350, 50),
                                                               Vector2(100, 50));

    EntityId object2 = game->createEntity();
    PhysicsComponent *physicsComponent2 = new PhysicsComponent(object2,
                                                               BodyType::Static,
                                                               Vector2(460, 200),
                                                               Vector2(100, 50));

    EntityId object3 = game->createEntity();
    PhysicsComponent *physicsComponent3 = new PhysicsComponent(object3,
                                                               BodyType::Static,
                                                               Vector2(800, 500),
                                                               Vector2(600, 50));


    // TODO: Create Entity class which stores all the components as smart pointers?
    game->addComponent(object1, physicsComponent1);
    game->addComponent(object2, physicsComponent2);
    game->addComponent(object3, physicsComponent3);
}
