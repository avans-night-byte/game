#include "CharacterComponent.hpp"

#include "../Game.hpp"
#include "HealthComponent.hpp"

#include <memory>
#include "../../Engine/Managers/ResourceManager.hpp"

CharacterComponent::CharacterComponent(EntityId id) : Component(id), spriteSheet(nullptr) {
}

string CharacterComponent::name() const {
    return "CharacterComponent";
}

CharacterComponent::CharacterComponent(EntityId id, const Vector2 &position)
        : Component(id) {
    Game *game = Game::getInstance();

    this->resetMovement();
    physicsComponent = std::make_unique<PhysicsComponent>(id,
                                                          BodyType::Dynamic,
                                                          Vector2(position.x, position.y),
                                                          Vector2(20, 20));
    physicsComponent->setFixedRotation(true);
    physicsComponent->setVelocity(Vector2());

    spriteSheet = game->getRenderingApi().createSpriteSheet("../../Resources/Sprites/character.png",
                                                             "spritesheet_char", 100, 105);

    worldPosition = std::make_unique<TransformComponent>(id);
    healthComponent = make_unique<HealthComponent>();

    game->addComponent(id, worldPosition.get());
    game->addComponent(id, physicsComponent.get());

    const RPosition &rPosition = physicsComponent->getRPosition();
    worldPosition->refLocation(rPosition.X, rPosition.Y);
    worldPosition->setRotation(rPosition.rotation);

    spriteSheet->select_sprite(0, 0);
}

void CharacterComponent::update(const Input &inputSystem) {
    bool stopped = false;

    //TODO: Move naar _engine
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

    if(inputSystem.keyMap.action == "ESCAPE"){
        auto& p = *ResourceManager::getInstance();
        p.loadResource("Options");

    }


    auto& inputApi = Game::getInstance()->getInputAPI();

    int mx, my;
    inputApi.getMousePosition(mx, my);

    auto mouseVector = Vector2(mx, my);
    auto worldPos = Vector2(*worldPosition->physicsX, *worldPosition->physicsY);
    auto mouseAngle = atan2(mouseVector.y - worldPos.y, mouseVector.x - worldPos.x);

    const RPosition &rPosition = physicsComponent->getRPosition();
    worldPosition->setRotation(rPosition.rotation);

    physicsComponent->setAngle(mouseAngle);
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

Component *CharacterComponent::clone(EntityId entityId, const Components::component *component) {
    return new CharacterComponent(entityId);
}


void CharacterComponent::render() {
    spriteSheet->draw_selected_sprite(*worldPosition->physicsX - 42.5f, *worldPosition->physicsY - 75.0f, 1,
                                      worldPosition->rotation);
}

void CharacterComponent::startContact(b2Contact *contact) {

}

void CharacterComponent::endContact(b2Contact *contact) {

}

void CharacterComponent::initialize(EntityObject &entityParent) {

}

