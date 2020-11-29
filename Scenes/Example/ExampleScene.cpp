#include "ExampleScene.hpp"

void ExampleScene::initialize() {
    Game *game = Game::getInstance();

    EntityId object1 = game->createEntity();
    auto *physicsComponent1 = new PhysicsComponent(object1,
                                                   BodyType::Dynamic,
                                                   Vector2(450, 150),
                                                   Vector2(100, 50));
    EntityId object5 = game->createEntity();
    auto *physicsComponent5 = new PhysicsComponent(object1,
                                                   BodyType::Dynamic,
                                                   Vector2(450, 150),
                                                   50.0f);


    EntityId object2 = game->createEntity();
    auto *physicsComponent2 = new PhysicsComponent(object2,
                                                   BodyType::Static,
                                                   Vector2(640, 200),
                                                   Vector2(100, 50));

    EntityId object3 = game->createEntity();
    auto *physicsComponent3 = new PhysicsComponent(object3,
                                                   BodyType::Static,
                                                   Vector2(1000, 500),
                                                   Vector2(600, 50));

    EntityId object4 = game->createEntity();
    auto *physicsComponent4 = new PhysicsComponent(object4,
                                                   BodyType::Static,
                                                   Vector2(0, 800),
                                                   Vector2(10000, 50));

    // TODO: Create Entity class which stores all the components as smart pointers?
    game->addComponent(object1, physicsComponent1);
    game->addComponent(object2, physicsComponent2);
    game->addComponent(object3, physicsComponent3);
    game->addComponent(object4, physicsComponent4);
    game->addComponent(object5, physicsComponent5);

    entities.push_back(object1);
    entities.push_back(object2);
    entities.push_back(object3);
    entities.push_back(object4);
    entities.push_back(object5);
}


void ExampleScene::fixedUpdate(const float &deltaTime) {
    characterComponent.fixedUpdate(deltaTime);
}

void ExampleScene::update(const Input &inputSystem) {
    characterComponent.update(inputSystem);
}
