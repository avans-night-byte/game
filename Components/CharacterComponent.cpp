#include "CharacterComponent.hpp"

#include "../Game.hpp"
#include "HealthComponent.hpp"

#include <memory>
#include "../../Engine/Managers/ResourceManager.hpp"
#include "WeaponComponent.hpp"

CharacterComponent::CharacterComponent(EntityId id) : Component(id), _pSpriteSheet(nullptr) {
}

string CharacterComponent::name() const {
    return "CharacterComponent";
}

CharacterComponent::CharacterComponent(EntityId id, const Vector2 &position)
        : Component(id) {
    Game *game = Game::getInstance();

    this->resetMovement();
    _physicsComponent = std::make_unique<PhysicsComponent>(id,
                                                           BodyType::Dynamic,
                                                           Vector2(position.x, position.y),
                                                           20.0f);
    _physicsComponent->setFixedRotation(true);
    _physicsComponent->setVelocity(Vector2());

    _pSpriteSheet = game->getRenderingApi().createSpriteSheet("../../Resources/Sprites/character.png",
                                                              "spritesheet_char", 100, 105);

    _transform = std::make_unique<TransformComponent>(id);
    _healthComponent = make_unique<HealthComponent>();

    game->addComponent(id, _transform.get());
    game->addComponent(id, _physicsComponent.get());

    const RTransform &rPosition = _physicsComponent->getRTransform();
    _transform->refLocation(rPosition.X, rPosition.Y);
    _transform->setRotation(rPosition.rotation);

    _pSpriteSheet->select_sprite(0, 0);
}

void CharacterComponent::update(const Input &inputSystem) {
    bool stopped = false;

    //TODO: Move naar _engine
    if (inputSystem.keyMap.type == SDL_KEYUP) {
        stopped = true;
    }

    if (inputSystem.keyMap.action == "UP") {
        _currentMovementDirection[MovementDirection::Up] = !stopped;
    }
    if (inputSystem.keyMap.action == "DOWN") {
        _currentMovementDirection[MovementDirection::Down] = !stopped;
    }
    if (inputSystem.keyMap.action == "RIGHT") {
        _currentMovementDirection[MovementDirection::Right] = !stopped;
    }
    if (inputSystem.keyMap.action == "LEFT") {
        _currentMovementDirection[MovementDirection::Left] = !stopped;
    }

    if (inputSystem.keyMap.action == "ESCAPE") {
        auto &p = *ResourceManager::getInstance();
        p.loadResource("Options");
    }

    if (inputSystem.keyMap.action == "CLICK_LEFT") {
        _weapon->shoot(*_transform);
    }


    auto &inputApi = Game::getInstance()->getInputAPI();

    int mx, my;
    inputApi.getMousePosition(mx, my);

    auto mouseVector = Vector2(mx, my);
    auto worldPos = Vector2(*_transform->physicsX, *_transform->physicsY);
    auto mouseAngle = atan2(mouseVector.y - worldPos.y, mouseVector.x - worldPos.x);

    const RTransform &rPosition = _physicsComponent->getRTransform();
    _transform->setRotation(rPosition.rotation);
    
    _physicsComponent->setAngle(mouseAngle);
}

void CharacterComponent::fixedUpdate(const float &deltaTime) {
    Vector2 velocity;
    getVelocity(velocity);

    map<MovementDirection, bool>::iterator it;
    bool movingHor = false;
    bool movingVer = false;

    for (it = _currentMovementDirection.begin(); it != _currentMovementDirection.end(); it++) {
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
    _currentMovementDirection[Left] = false;
    _currentMovementDirection[Right] = false;
    _currentMovementDirection[Up] = false;
    _currentMovementDirection[Down] = false;
}

Component *CharacterComponent::clone(EntityId entityId, const Components::component *component) {
    return new CharacterComponent(entityId);
}


void CharacterComponent::render() {
    _pSpriteSheet->draw_selected_sprite(*_transform->physicsX - 42.5f, *_transform->physicsY - 75.0f, 1,
                                        _transform->rotation);
}

void CharacterComponent::startContact(b2Contact *contact) {

}

void CharacterComponent::endContact(b2Contact *contact) {

}

void CharacterComponent::initialize(EntityObject &entityParent) {

}

// TODO: Write a global-object-resource file that can load every globally used objects (weapons, bullets, characters)
void CharacterComponent::initializeWeapons(std::vector<std::unique_ptr<EntityObject>> &entities) {
    for (auto &entity : entities) {
        if (auto *bullet = entity->getComponent<BulletComponent>()) {
            auto id = getEntityId();
            _weapon = std::make_unique<WeaponComponent>(id, *entity);
            break;
        }
    }
}

