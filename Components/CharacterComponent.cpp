#include "CharacterComponent.hpp"

#include "../Game.hpp"

CharacterComponent::CharacterComponent(EntityId id) : Component(id), spriteSheet(nullptr) {

}

string CharacterComponent::name() const {
    return "CharacterComponent";
}

CharacterComponent::CharacterComponent(EntityId id, const Vector2 &position)
        : Component(id) {
    Game *game = Game::getInstance();

    this->resetMovement();
    physicsComponent = make_unique<PhysicsComponent>(id,
                                                     BodyType::Dynamic,
                                                     Vector2(position.x, position.y),
                                                     Vector2(20, 20));
    physicsComponent->setFixedRotation(true);
    physicsComponent->setVelocity(Vector2());

    spriteSheet = game->getRenderingApi()->createSpriteSheet("../../Resources/Sprites/character.png",
                                                             "spritesheet_char", 8, 11, 100, 105);

    worldPosition = make_unique<WorldPositionComponent>(id);


    game->addComponent(id, worldPosition.get());
    game->addComponent(id, physicsComponent.get());

    const RPosition &rPosition = physicsComponent->getRPosition();
    worldPosition->setLocation(rPosition.X, rPosition.Y);

    spriteSheet->select_sprite(0, 0);
}

void CharacterComponent::update(const Input &inputSystem) {
    bool stopped = false;

    if (inputSystem.keyMap.type == SDL_KEYUP) {
        stopped = true;
    }

    if (inputSystem.keyMap.action == "UP") {
        currentMovementDirection[MovementDirection::Up] = !stopped;
    }
    if (inputSystem.keyMap.action == "DOWN") {
        currentMovementDirection[MovementDirection::Down] = !stopped;
    }
    if (inputSystem.keyMap.action == "RIGHT") {
        currentMovementDirection[MovementDirection::Right] = !stopped;
    }
    if (inputSystem.keyMap.action == "LEFT") {
        currentMovementDirection[MovementDirection::Left] = !stopped;
    }

    update();
}

void CharacterComponent::fixedUpdate(const float &deltaTime) {
    Vector2 velocity;
    getVelocity(velocity);

    map<MovementDirection, bool>::iterator it;
    bool movingHor = false;
    bool movingVer = false;

    for (it = currentMovementDirection.begin(); it != currentMovementDirection.end(); it++) {
        switch (it->first) {
            case Left:
                if (!it->second && movingHor != true) {
                    velocity.x = 0;
                    movingHor = false;
                    break;
                }

                if (movingHor)
                    break;

                velocity.x = -2000;
                movingHor = true;
                break;
            case Right:
                if (!it->second && !movingHor) {
                    velocity.x = 0;
                    movingHor = false;
                    break;
                }
                if (movingHor)
                    break;

                velocity.x = 2000;
                movingHor = true;
                break;
            case Up:
                if (!it->second && !movingVer) {
                    velocity.y = 0;
                    movingVer = false;
                    break;
                }
                if (movingVer)
                    break;

                velocity.y = -2000;
                movingVer = true;
                break;
            case Down:
                if (!it->second && !movingVer) {
                    velocity.y = 0;
                    movingVer = false;
                    break;
                }
                if (movingVer)
                    break;

                velocity.y = 2000;
                movingVer = true;
                break;
        }

        setVelocity(velocity * deltaTime);

    }
}

void CharacterComponent::resetMovement() {
    currentMovementDirection[Left] = false;
    currentMovementDirection[Right] = false;
    currentMovementDirection[Up] = false;
    currentMovementDirection[Down] = false;
}

Component *CharacterComponent::clone(EntityId entityId, const LevelResources::component *component) {
    return new CharacterComponent(entityId);
}

void CharacterComponent::startContact() {

}

void CharacterComponent::endContact() {

}
